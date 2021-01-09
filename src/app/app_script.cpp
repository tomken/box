
#include "app_script.h"

#include <math.h>

#define countof(x) (sizeof(x) / sizeof((x)[0]))

#define UTF8_CHAR_LEN_MAX 6

static JSValue js_print(JSContext *ctx,
                        JSValueConst this_val,
                        int argc, JSValueConst *argv)
{
    int i;
    const char *str;
    
    for(i = 0; i < argc; i++) {
        if (i != 0)
            putchar(' ');
        str = JS_ToCString(ctx, argv[i]);
        if (!str)
            return JS_EXCEPTION;
        fputs(str, stdout);
        JS_FreeCString(ctx, str);
    }
    putchar('\n');
    return JS_UNDEFINED;
}

namespace app {
    
    static JSClassID js_data_id;
    
    void setPrivateData(JSContext* ctx, JSValue value, void* data) {
        JSValue obj = JS_NewObjectClass(ctx, js_data_id);
        JS_SetOpaque(obj, data);
        JS_SetPropertyStr(ctx, value, "__data__", obj);
    }
    
    void* getPrivateData(JSContext* ctx, JSValue value) {
        JSValue obj = JS_GetPropertyStr(ctx, value, "__data__");
        void* data = JS_GetOpaque(obj, js_data_id);
        JS_FreeValue(ctx, obj);
        return data;
    }
    
    /* Point Class */
    
    typedef struct {
        int x;
        int y;
    } JSPointData;
    
    static JSClassID js_point_class_id;
    
    static void js_point_finalizer(JSRuntime *rt, JSValue val)
    {
        JSPointData *s = (JSPointData*)JS_GetOpaque(val, js_point_class_id);
        /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
        js_free_rt(rt, s);
    }
    
    static JSValue js_point_ctor(JSContext *ctx,
                                 JSValueConst new_target,
                                 int argc, JSValueConst *argv)
    {
        JSPointData *s;
        JSValue obj = JS_UNDEFINED;
        JSValue proto;
        
        s = (JSPointData*)js_mallocz(ctx, sizeof(*s));
        if (!s)
            return JS_EXCEPTION;
        if (JS_ToInt32(ctx, &s->x, argv[0]))
            goto fail;
        if (JS_ToInt32(ctx, &s->y, argv[1]))
            goto fail;
        /* using new_target to get the prototype is necessary when the
         class is extended. */
        proto = JS_GetPropertyStr(ctx, new_target, "prototype");
        if (JS_IsException(proto))
            goto fail;
        obj = JS_NewObjectProtoClass(ctx, proto, js_point_class_id);
        JS_FreeValue(ctx, proto);
        if (JS_IsException(obj))
            goto fail;
        JS_SetOpaque(obj, s);
        return obj;
    fail:
        js_free(ctx, s);
        JS_FreeValue(ctx, obj);
        return JS_EXCEPTION;
    }
    
    static JSValue js_point_get_xy(JSContext *ctx, JSValueConst this_val, int magic)
    {
        JSPointData *s = (JSPointData*)JS_GetOpaque2(ctx, this_val, js_point_class_id);
        if (!s)
            return JS_EXCEPTION;
        if (magic == 0)
            return JS_NewInt32(ctx, s->x);
        else
            return JS_NewInt32(ctx, s->y);
    }
    
    static JSValue js_point_set_xy(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
    {
        JSPointData *s = (JSPointData*)JS_GetOpaque2(ctx, this_val, js_point_class_id);
        int v;
        if (!s)
            return JS_EXCEPTION;
        if (JS_ToInt32(ctx, &v, val))
            return JS_EXCEPTION;
        if (magic == 0)
            s->x = v;
        else
            s->y = v;
        return JS_UNDEFINED;
    }
    
    static JSValue js_point_norm(JSContext *ctx,
                                 JSValueConst this_val,
                                 int argc, JSValueConst *argv)
    {
        JSPointData *s = (JSPointData*)JS_GetOpaque2(ctx, this_val, js_point_class_id);
        if (!s)
            return JS_EXCEPTION;
        return JS_NewFloat64(ctx, sqrt((double)s->x * s->x + (double)s->y * s->y));
    }
    
    static JSClassDef js_point_class = {
        "Point",
        .finalizer = js_point_finalizer,
    };
    
    static const JSCFunctionListEntry js_point_proto_funcs[] = {
        JS_CGETSET_MAGIC_DEF("x", js_point_get_xy, js_point_set_xy, 0),
        JS_CGETSET_MAGIC_DEF("y", js_point_get_xy, js_point_set_xy, 1),
        JS_CFUNC_DEF("norm", 0, js_point_norm),
    };
    
    static int _ModuleStub(JSContext* ctx, JSModuleDef* m) {
        JSAtom atom = JS_GetModuleName(ctx, m);
        ScriptContext* script = (ScriptContext*)JS_GetContextOpaque(ctx);
        if (!script) {
            return 0;
        }
        
        ScriptModule* module = script->findModule(atom);
        if (!module) {
            return 0;
        }
        
        std::vector<ScriptModuleItem>& list = module->exports();
        std::vector<ScriptModuleItem>::iterator it;
        for (it = list.begin(); it != list.end(); ++it) {
            ScriptModuleItem& item = *it;
            if (item.isClass) {
                
            } else {
                JS_SetModuleExport(ctx, m, item.name.c_str(), item.value);
            }
        }
        
        JSValue point_proto, point_class;
        
        /* create the Point class */
        JS_NewClassID(&js_point_class_id);
        JS_NewClass(JS_GetRuntime(ctx), js_point_class_id, &js_point_class);
        
        point_proto = JS_NewObject(ctx);
        JS_SetPropertyFunctionList(ctx, point_proto, js_point_proto_funcs, countof(js_point_proto_funcs));
        
        point_class = JS_NewCFunction2(ctx, js_point_ctor, "Point", 2, JS_CFUNC_constructor, 0);
        /* set proto.constructor and ctor.prototype */
        JS_SetConstructor(ctx, point_class, point_proto);
        JS_SetClassProto(ctx, js_point_class_id, point_proto);
        
        JS_SetModuleExport(ctx, m, "Point", point_class);
//        JS_SetModuleExport(ctx, m, "height", JS_NewInt32(ctx, 101));
        return 0;
    }
    
    ScriptModule::ScriptModule(JSContext* ctx, const char* name) : _ctx(ctx), _name(name) {
        _m = JS_NewCModule(ctx, name, _ModuleStub);
//        JS_AddModuleExport(ctx, _m, "Point");
//        JS_AddModuleExport(ctx, _m, "height");
    }
    
    ScriptModule::~ScriptModule() {
        
    }
    
    ScriptValue ScriptContext::evalFile(const char* filename) {
        FILE* file = fopen(filename, "rb");
        if (!file)
            return ScriptValue(ctx, JS_NULL);
        
        fseek(file, 0L, SEEK_END);
        long len = ftell(file);
        char* p = (char *)malloc(len+1);
        fseek(file, 0L, SEEK_SET);
        fread(p, len, 1, file);
        p[len]=0;
        fclose(file);
        
        return eval(p, len, filename);
    }
    
    void ScriptContext::addConsole() {
        JSValue global_obj, console, args;
        int i;
        
        /* XXX: should these global definitions be enumerable? */
        global_obj = JS_GetGlobalObject(ctx);
        
        console = JS_NewObject(ctx);
        JS_SetPropertyStr(ctx, console, "log",
                          JS_NewCFunction(ctx, js_print, "log", 1));
        JS_SetPropertyStr(ctx, global_obj, "console", console);
        
        JS_SetPropertyStr(ctx, global_obj, "print",
                          JS_NewCFunction(ctx, js_print, "print", 1));
        
        JS_FreeValue(ctx, global_obj);
    }
}


#ifndef __APP_SCRIPT_H__
#define __APP_SCRIPT_H__

#include <string>
#include <vector>
#include <map>

#include "app_bind.h"

#include "../quickjs/quickjs.h"

namespace app {
    
    void setPrivateData(JSContext* ctx, JSValue value, void* data);
    void* getPrivateData(JSContext* ctx, JSValue value);
    
    static JSValue ScriptStub(JSContext* ctx,
                              JSValue this_value,
                              int argc, JSValue * argv);
    
    class ScriptValue;
    typedef typename std::vector<ScriptValue> ScriptArgs;
    
    class ScriptContext;
    typedef typename app::Callable<void(const ScriptContext&, const ScriptArgs& args)> ScriptFunctionCb;
    
    class ScriptFunction {
    public:
        ScriptFunction(ScriptFunctionCb cb) {
            _cb   = cb;
        }
        
    public:
        ScriptFunctionCb _cb;
    };
    
    template <typename R>
    struct ScriptTraits {
    };
    
    template <>
    struct ScriptTraits<JSValue> {
        static JSValue unwrap(JSContext * ctx, JSValue v) noexcept {
            return v;
        }
        
        static JSValue wrap(JSContext * ctx, JSValue v) noexcept {
            return v;
        }
    };
    
    template <>
    struct ScriptTraits<bool> {
        static bool unwrap(JSContext * ctx, JSValue v) {
            return JS_ToBool(ctx, v);
        }
        
        static JSValue wrap(JSContext * ctx, bool i) noexcept {
            return JS_NewBool(ctx, i);
        }
    };
    
    template <>
    struct ScriptTraits<int32_t> {
        static int32_t unwrap(JSContext * ctx, JSValue v) {
            int32_t r;
            if (JS_ToInt32(ctx, &r, v)) {
                assert(0);
            }
            return r;
        }
        
        static JSValue wrap(JSContext * ctx, int32_t i) noexcept {
            return JS_NewInt32(ctx, i);
        }
    };
    
    template <>
    struct ScriptTraits<float> {
        static double unwrap(JSContext * ctx, JSValue v) {
            double r;
            if (JS_ToFloat64(ctx, &r, v)) {
                assert(0);
            }
            return r;
        }
        
        static JSValue wrap(JSContext * ctx, float v) noexcept {
            return JS_NewFloat64(ctx, v);
        }
    };
    
    template <>
    struct ScriptTraits<double> {
        static double unwrap(JSContext * ctx, JSValue v) {
            double r;
            if (JS_ToFloat64(ctx, &r, v)) {
                assert(0);
            }
            return r;
        }
        
        static JSValue wrap(JSContext * ctx, double v) noexcept {
            return JS_NewFloat64(ctx, v);
        }
    };
    
    template <>
    struct ScriptTraits<const char*> {
        static const char* unwrap(JSContext * ctx, JSValue v) {
            return JS_ToCString(ctx, v);
        }
        
        static JSValue wrap(JSContext * ctx, const char* str) noexcept {
            return JS_NewString(ctx, str);
        }
    };
    
    class ScriptValue;
    template <>
    struct ScriptTraits<ScriptValue>;
    
    static JSClassID js_function_class_id;
    
    template <>
    struct ScriptTraits<ScriptFunctionCb> {
//        static const char* unwrap(JSContext * ctx, JSValue v) {
//            return JS_NewCFunction(ctx, ScriptStup, "1", 1);
//        }
        
        static JSValue wrap(JSContext* ctx, ScriptFunctionCb cb) noexcept {
            JSValue f = JS_NewCFunction(ctx, ScriptStub, NULL, 1);
            setPrivateData(ctx, f, new ScriptFunction(cb));
            return f;
        }
    };
    
    class ScriptValue;
    struct ScriptProperty {
        JSContext*  ctx;
        JSValue     thiz;
        const char* name;
        
    public:
        operator JSValue() const {
            return JS_GetPropertyStr(ctx, thiz, name);
        }
        
        template <typename Value>
        ScriptProperty& operator= (Value value) {
            JSValue v = ScriptTraits<Value>::wrap(ctx, value);
            JS_SetPropertyStr(ctx, thiz, name, v);
            return *this;
        }
    };
    
    class ScriptValue {
    public:
        template <typename T>
        ScriptValue(JSContext* ctx, T val) : _ctx(ctx) {
            _val = ScriptTraits<T>::wrap(ctx, val);
        }
        
        ScriptValue(const ScriptValue& rhs) {
            _ctx = rhs._ctx;
            _val = JS_DupValue(_ctx, rhs._val);
        }
        
        ~ScriptValue() {
            if (_ctx) JS_FreeValue(_ctx, _val);
        }
        
    public:
        ScriptProperty operator [](const char* key) {
            return {_ctx, _val, key};
        }
        
        template <typename T>
        T cast() const {
            return ScriptTraits<T>::unwrap(_ctx, _val);
        }
        
        bool isNull()      const { return JS_IsNull(_val);           }
        bool isUndefined() const { return JS_IsUndefined(_val);      }
        bool isBool()      const { return JS_IsBool(_val);           }
        bool isNumber()    const { return JS_IsNumber(_val);         }
        bool isString()    const { return JS_IsString(_val);         }
        bool isFunction()  const { return JS_IsFunction(_ctx, _val); }
        bool isObject()    const { return JS_IsObject(_val);         }
        bool isException() const { return JS_IsException(_val);      }
        
        JSValue release() {
            _ctx = nullptr;
            return _val;
        }
        
    private:
        JSContext* _ctx = nullptr;
        JSValue    _val;
    };
    
    template <>
    struct ScriptTraits<ScriptValue> {
        static ScriptValue unwrap(JSContext* ctx, JSValue v) {
            return ScriptValue(ctx, v);
        }
        
        static JSValue wrap(JSContext* ctx, ScriptValue v) noexcept {
            return v.release();
        }
    };
    
    class ScriptModuleItem {
    public:
        std::string name;
        JSValue     value;
        bool        isClass;
    };
    
    class ScriptModule {
        friend class ScriptContext;
    public:
        ScriptModule(JSContext* ctx, const char* name);
        ~ScriptModule();
        
    public:
        ScriptModule& addValue(const char* name, JSValue value) {
            ScriptModuleItem item;
            item.name    = name;
            item.value   = value;
            item.isClass = false;
            _exports.push_back(item);
            JS_AddModuleExport(_ctx, _m, name);
            return *this;
        }
        
        ScriptModule& addValue(const char* name, ScriptValue value) {
            return addValue(name, value.release());
        }
        
        template <typename T>
        ScriptModule& addValue(const char* name, T value) {
            JSValue v = ScriptTraits<T>::wrap(_ctx, value);
            return addValue(name, v);
        }
        
        template <typename T>
        ScriptModule& addClass(const char* name, ScriptValue value) {
            JS_AddModuleExport(_ctx, _m, name);
            return *this;
        }
        
    public:
        std::vector<ScriptModuleItem>& exports() {
            return _exports;
        }
        
    private:
        JSContext*   _ctx;
        JSModuleDef* _m;
        const char*  _name;
        
        std::vector<ScriptModuleItem> _exports;
    };
    
    class ScriptRuntime {
        friend class ScriptContext;
    public:
        ScriptRuntime() {
            rt = JS_NewRuntime();
        }
        
        ~ScriptRuntime() {
            JS_FreeRuntime(rt);
        }
        
    private:
        JSRuntime* rt;
    };
    
    template <typename T>
    class ScriptClass {
        inline static JSClassID _ClassId;
    public:
        static JSValue _ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv) {
            JSValue obj = JS_NewObjectClass(ctx, _ClassId);
            setPrivateData(ctx, obj, new T());
            return obj;
        }
        
        static void _finalizer(JSRuntime *rt, JSValue val) {
            T* obj = (T*)JS_GetOpaque(val, ScriptClass::_ClassId);
            delete obj;
        }
        
        static JSValue registerClass(JSContext* ctx, ScriptValue obj) {
            JSClassDef classDef = {
                "name",
                .finalizer = ScriptClass::_finalizer,
            };
            JS_NewClassID(&_ClassId);
            JS_NewClass(JS_GetRuntime(ctx), _ClassId, &classDef);
            
            JSValue proto = obj.release();
            JS_SetClassProto(ctx, _ClassId, proto);
            
            JSValue class_ctor = JS_NewCFunction2(ctx, _ctor, "", 0, JS_CFUNC_constructor, 0);
            return class_ctor;
//            JSValue global = JS_GetGlobalObject(ctx);
//            JS_SetPropertyStr(ctx, global, name, class_ctor);
//            JS_FreeValue(ctx, global);
        }
    };
    
    class ScriptContext {
    public:
        ScriptContext(ScriptRuntime& rt) {
            ctx = JS_NewContext(rt.rt);
            JS_SetContextOpaque(ctx, this);
            
            addConsole();
        }
        
        ~ScriptContext() {
            JS_SetContextOpaque(ctx, 0);
            JS_FreeContext(ctx);
        }
        
        ScriptValue global() {
            return ScriptValue{ctx, JS_GetGlobalObject(ctx)};
        }
        
        std::string getException() {
            JSValue value = JS_GetException(ctx);
            
            JSValue fileName = JS_GetPropertyStr(ctx, value, "fileName");
            const char* fileName_c = JS_ToCString(ctx, fileName);
            
            JSValue lineNumber = JS_GetPropertyStr(ctx, value, "lineNumber");
            const char* lineNumber_c = JS_ToCString(ctx, lineNumber);
            
            JSValue message = JS_GetPropertyStr(ctx, value, "message");
            const char* message_c = JS_ToCString(ctx, message);
            
            JSValue stack = JS_GetPropertyStr(ctx, value, "stack");
            const char* stack_c = JS_ToCString(ctx, stack);
            
            std::string info = "\n";
            info += "stack:";
            info += stack_c;
            info += "message:";
            info += message_c;
            
            JS_FreeCString(ctx, stack_c);
            JS_FreeCString(ctx, message_c);
            JS_FreeCString(ctx, lineNumber_c);
            JS_FreeCString(ctx, fileName_c);
            
            JS_FreeValue(ctx, stack);
            JS_FreeValue(ctx, message);
            JS_FreeValue(ctx, lineNumber);
            JS_FreeValue(ctx, fileName);
            
            JS_FreeValue(ctx, value);
            return info;
        }
        
        ScriptValue newObject() {
            return ScriptValue{ctx, JS_NewObject(ctx)};
        }
        
        ScriptModule& addModule(const char* name) {
            JSAtom atom = JS_NewAtom(ctx, name);
            std::map<JSAtom, ScriptModule*>::iterator it;
            it = modules.find(atom);
            if (it != modules.end())
                return *(it->second);
   
            ScriptModule* module = new ScriptModule(ctx, name);
            modules[atom] = module;
            return *module;
        }
        
        template <typename T>
        JSValue registerClass(ScriptValue proto) {
            JSValue v = ScriptClass<T>::registerClass(ctx, proto);
            return v;
        }
        
        ScriptValue eval(const char* script, int size, const char* filename) {
            JSValue v = JS_Eval(ctx, script, size, filename, JS_EVAL_TYPE_MODULE);
            return ScriptValue{ctx, v};
        }
        
        ScriptValue evalFile(const char* filename);
        
    public:
        ScriptModule* findModule(JSAtom name) {
            std::map<JSAtom, ScriptModule*>::iterator it;
            it = modules.find(name);
            if (it != modules.end())
                return it->second;
            
            return 0;
        }
        
    private:
        void addConsole();
        
    private:
        JSContext* ctx;
        
        std::map<JSAtom, ScriptModule*>    modules;
        std::map<std::string, ScriptFunctionCb> cbs;
    };
    
    static JSValue ScriptStub(JSContext* ctx,
                              JSValueConst this_value,
                              int argc, JSValueConst * argv) {
        JSValue function = argv[-1];
        ScriptContext* c = (ScriptContext*)JS_GetContextOpaque(ctx);
        ScriptFunction* func = (ScriptFunction*)getPrivateData(ctx, function);
        if (func) {
            void* thiz = getPrivateData(ctx, this_value);
            
            ScriptArgs cb_args;
            for (int i=0; i<argc; i++) {
                cb_args.push_back(ScriptValue(ctx, argv[i]));
            }
            
            if (thiz) {
                func->_cb.apply(thiz)(*c, cb_args);
            } else {
                func->_cb(*c, cb_args);
            }
        }
        return JS_UNDEFINED;
    }

}

#endif // __APP_SCRIPT_H__

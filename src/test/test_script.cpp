
#include "app/app_script.h"

void print_cb(const app::ScriptContext& ctx, const app::ScriptArgs& args) {
    int index = 0;
    printf("Script callback:\n");
    app::ScriptArgs::const_iterator it;
    for (it = args.begin(); it != args.end(); ++it) {
        const app::ScriptValue& value = *it;
        
        printf("  argv[%d] = ", index);
        
        if (value.isBool()) {
            printf("%s\n", value.cast<bool>() ? "true" : "false");
        } else if (value.isNumber()) {
            printf("%0.2f\n", value.cast<double>());
        } else if (value.isString()) {
            printf("%s\n", value.cast<const char*>());
        } else if (value.isObject()) {
            printf("%s\n", value.cast<const char*>());
        } else {
            assert(0);
        }
    }
}


class AA {
public:
    AA() {
        value = 100;
    }
    
public:
    int getValue() {
        return value;
    }
    
    void print(const app::ScriptContext& ctx, const app::ScriptArgs& args) {
        printf("AA %p print\n", this);
        print_cb(ctx, args);
    }
    
public:
    void initScript(app::ScriptContext& ctx) {
        app::ScriptValue obj = ctx.newObject();
        obj["setValue"] = app::bind(&print_cb);
        ctx.registerClass<AA>(obj);
    }
    
public:
    int value;
};

void test_bind() {
    typedef typename app::Callable<int()> TestCb;
    
    AA* aa1 = new AA();
    aa1->value = 2;
    AA* aa2 = new AA();
    aa2->value = 3;
    
    TestCb cb = app::bind(&AA::getValue, aa1);
    int value = cb.apply(aa2)();
    printf("AA value=%d\n", value);
    exit(0);
}

// add module
//    ScriptModule& m = ctx.addModule("lmk");
//    m.addValue("width", 100);
//    m.addClass<AA>("AA", obj);
// m.add("bridge", ScriptFunction("call", app::bind(&print_cb)));


void test_script() {
    app::ScriptRuntime rt;
    app::ScriptContext ctx(rt);
    
    // add global function and vars
    app::ScriptValue version = ctx.newObject();
    version["major"] = 1;
    version["minor"] = 3;
    app::ScriptValue global = ctx.global();
    global["version"] = version;
    
    // register class and add to global
    app::ScriptValue obj = ctx.newObject();
    obj["i"] = 54;
    obj["f"] = 1.5f;
    obj["name"] = "hello";
    obj["cb"] = app::bind(&AA::print, (AA*)0);
    global["AA"] = ctx.registerClass<AA>(obj);
    
    app::ScriptValue value = ctx.evalFile("/Users/zy/peter/peter/box/script/test.js");
    if (value.isException()) {
        printf("JS Exception:%s\n", ctx.getException().c_str());
    }
}

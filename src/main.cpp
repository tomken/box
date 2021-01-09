#include "window_box.h"
#include "window_push_box.h"
#include "window_five.h"
#include "window_link.h"

#include "app/app_init.h"
#include "app/app_script.h"

#include "os/app_data_owner.h"
#include "nlohmann/json.hpp"

struct AClass {
    AClass() {
        printf("A - new %p\n", this);
        value = 100;
    }
    
    ~AClass() {
        printf("A - delete %p\n", this);
    }
    
    int value;

};

app::DataOwner<AClass> a_owner;

static DataID test_memory() {
//    AClass* v = mem_new(AClass);
//    printf("a sizeof=%d ptr=%p\n", sizeof(AClass), v);
//    mem_delete(v);
    
    AClass a;
//    a.value = 10;
    DataID did1 = a_owner.makeDataId(a);
    DataID did2 = a_owner.makeDataId(a);
    printf("DataID=%llu count=%u\n", did1.getId(), a_owner.getCount());
    printf("DataID=%llu count=%u\n", did2.getId(), a_owner.getCount());
//    a_owner.free(did1);
    a_owner.free(did2);
    
    return did1;
}

static void test() {
    DataID did = test_memory();
    
    AClass* a1 = a_owner.getPtr(did);
    
    if (a1) {
        printf("DataID=%llu count=%u a=%p a.value=%d\n",
               did.getId(), a_owner.getCount(), a1, a1->value);
    } else {
        printf("DataID=%llu count=%u a=%p\n",
               did.getId(), a_owner.getCount(), a1);
    }
    
//    a1->value = 99;
//    AClass* a2 = a_owner.getPtr(did);
//    printf("DataID=%llu count=%u a=%p a.value=%d\n", did.getId(), a_owner.getCount(), a2, a1->value);
}

void script_cb(const ScriptContext& ctx) {
    
}

void print_cb(const ScriptContext& ctx, const ScriptArgs& args) {
    int index = 0;
    printf("Script callback:\n");
    ScriptArgs::const_iterator it;
    for (it = args.begin(); it != args.end(); ++it) {
        const ScriptValue& value = *it;
        
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
    
    void print(const ScriptContext& ctx, const ScriptArgs& args) {
        printf("AA %p print\n", this);
        print_cb(ctx, args);
    }
    
public:
    void initScript(ScriptContext& ctx) {
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
    
    ScriptValue value = ctx.evalFile("/Users/zy/peter/peter/box/script/test.js");
    if (value.isException()) {
        printf("JS Exception:%s\n", ctx.getException().c_str());
    }
}

// add module
//    ScriptModule& m = ctx.addModule("lmk");
//    m.addValue("width", 100);
//    m.addClass<AA>("AA", obj);
// m.add("bridge", ScriptFunction("call", app::bind(&print_cb)));

static void test_json() {
    nlohmann::json json;
    json['a'] = 1.0;
    exit(0);
}


int main(int argc, char* argv[]) {
//    test_bind();
//    test_script();
//    exit(0);
    
//    link::Engine engine;
//    engine.randomLevel();
//    return 0;
    
//    Box win;
//    boxes::Game win;
//    gobang::Game win;
    link::Game win;
    win.run();

    return 0;
}

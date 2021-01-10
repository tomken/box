
#include "os/app_data_owner.h"

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

static app::DataID test_memory() {
//    AClass* v = mem_new(AClass);
//    printf("a sizeof=%d ptr=%p\n", sizeof(AClass), v);
//    mem_delete(v);
    
    AClass a;
//    a.value = 10;
    app::DataID did1 = a_owner.makeDataId(a);
    app::DataID did2 = a_owner.makeDataId(a);
    printf("DataID=%llu count=%u\n", did1.getId(), a_owner.getCount());
    printf("DataID=%llu count=%u\n", did2.getId(), a_owner.getCount());
//    a_owner.free(did1);
    a_owner.free(did2);
    
    return did1;
}

void test_resource() {
    app::DataID did = test_memory();
    
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

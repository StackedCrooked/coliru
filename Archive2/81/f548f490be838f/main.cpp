#include <stdlib.h>
#include <stdio.h>

struct shared_ptr_s
{
//    struct impl_t* inst;
    int *use_cnt;
};

typedef struct shared_ptr_s shared_ptr_t;           // unadorned type
#define shared_ptr struct shared_ptr_s __attribute__((cleanup(free_shared)))

#define SHARED_PTR_GET_ADD_REF(sp_in, sp_name) ++(*sp_in.use_cnt); printf("add use_cnt = %d\n", *sp_in.use_cnt); shared_ptr sp_name = sp_in; 

void free_shared(struct shared_ptr_s* ptr)
{
    if(!ptr) return;
    printf("del use_cnt = %d\n", *ptr->use_cnt - 1); 
    if(0 == --(*ptr->use_cnt)) {
//        dtor(ptr->inst);
        printf("freeing %p\n", (void *)ptr->use_cnt);
        free(ptr->use_cnt);
    }
//    ptr->inst = 0;
    ptr->use_cnt = 0;
}

void func(shared_ptr_t sp)
{
    SHARED_PTR_GET_ADD_REF(sp, sp_loc);
    return;
}

int main(void)
{
    shared_ptr_t sp = {         // original type does not use __attribute__(cleanup)
//        .inst = ctor(), 
        .use_cnt = malloc(sizeof(int)) 
    };
    SHARED_PTR_GET_ADD_REF(sp, sp_loc);

    func(sp_loc);

    return 0;
}

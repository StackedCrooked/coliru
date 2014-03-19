#include <stdio.h>
typedef struct myArrayWrapper myArrayWrapper;
struct myArrayWrapper {
    int m_array[5];
};

void doSomething(myArrayWrapper a) {
    int* A = a.m_array;
    printf("\nbefore edit\n");
    for (size_t j = 0; j < 5; ++j)
       printf("%d ", A[j]);
    //edit
    for (size_t j = 0; j < 5; ++j)
       A[j] = 100;
    printf("\nafter edit\n");
    for (size_t j = 0; j < 5; ++j)
       printf("%d ", A[j]);
}

int main() {
    myArrayWrapper obj;
    obj.m_array[0] = 0;
    obj.m_array[1] = 1;
    obj.m_array[2] = 2;
    obj.m_array[3] = 3;
    obj.m_array[4] = 4;
    
    printf("\nbefore doSomething()\n");
    for (size_t j = 0; j < 5; ++j)
       printf("%d ", obj.m_array[j]);
    
    doSomething(obj);

    printf("\nafter doSomething()\n");
    for (size_t j = 0; j < 5; ++j)
       printf("%d ", obj.m_array[j]);

    return 0; 
}

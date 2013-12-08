#include <iostream>

int main() {


    int matrix[][3]{{1,2,3}, {4,5,6}, {7,8,9}};
    auto dyn_matrix = new int[3][3]{{1,2,3}, {4,5,6}, {7,8,9}};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << dyn_matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    //auto dummy = new int; (void)dummy;
    /* Uncommenting the previous line causes (with -O0):
    
a.out: malloc.c:2451: sYSMALLOc: Assertion `(old_top == (((mbinptr) (((char *) &((av)->bins[((1) - 1) * 2])) - __builtin_offsetof (struct malloc_chunk, fd)))) && old_size == 0) || ((unsigned long) (old_size) >= (unsigned long)((((__builtin_offsetof (struct malloc_chunk, fd_nextsize))+((2 * (sizeof(size_t))) - 1)) & ~((2 * (sizeof(size_t))) - 1))) && ((old_top)->size & 0x1) && ((unsigned long)old_end & pagemask) == 0)' failed.
bash: line 7:  6091 Aborted                 (core dumped) ./a.out

    */
    
    std::cout << "got here." << std::endl;

    return 0;   
}

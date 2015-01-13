//http://stackoverflow.com/questions/27933178/is-there-a-portable-way-to-find-out-what-alignments-are-supported-by-an-c11-impl

#include <stdlib.h>
#include <assert.h>

void* seriously_aligned_malloc(size_t alignment, size_t size) {
    assert(alignment<=255);
    char* allocated = (char*)malloc(size + alignment);
    unsigned char extraspace = (unsigned char)(alignment - (size_t)(allocated+alignment) % alignment);
    char* ptr = allocated + extraspace;
    unsigned char* extraspaceptr = (unsigned char*)(ptr - 1);
    *extraspaceptr = extraspace;
    return ptr;
}
void seriously_aligned_free(void* p) {
    char* ptr = (char*)p;
    unsigned char* extraspaceptr = (unsigned char*)(ptr - 1);
    unsigned char extraspace = *extraspaceptr;
    char* allocated = ptr - extraspace;
    free(allocated);
}

#include <stdio.h>

int main() {
    for(unsigned i=0; i<20; ++i) {
        char* p = (char*)seriously_aligned_malloc(7, 5);
        printf("%d", (size_t)p%7);
        seriously_aligned_free(p);
        p = (char*)seriously_aligned_malloc(7, 7);
        printf("%d", (size_t)p%7);
        seriously_aligned_free(p);
        p = (char*)seriously_aligned_malloc(7, 9);
        printf("%d", (size_t)p%7);
        seriously_aligned_free(p);
    }
    return 0;
}
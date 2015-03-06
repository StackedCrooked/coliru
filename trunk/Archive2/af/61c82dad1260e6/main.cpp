#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <stdio.h>
 
int main(void)
{
    char src[] = "hi";
    char dest[6] = "abcdef"; // no null terminator
    strncpy(dest, src, 5); // writes five characters 'h', 'i', '\0', '\0', '\0' to dest
    printf("strncpy(dst, src, 5) to a 6-byte dst gives : ");
    for(size_t n = 0; n < sizeof dest; ++n) {
        char c = dest[n];
        c ? printf("'%c' ", c) : printf("'\\0' ");
    }
 
    printf("\nstrncpy(dst2, src, 2) to a 2-byte dst gives : ");
    char dest2[2];
    strncpy(dest2, src, 2); // truncation: writes two characters 'a', 'b', to dest2
    for(size_t n = 0; n < sizeof dest2; ++n) {
        char c = dest2[n];
        c ? printf("'%c' ", c) : printf("'\\0' ");
    }
    printf("\n");
 
#ifdef __STDC_LIB_EXT1__
    char dst1[6], src1[100] = "hello";
    int r1 = strncpy_s(dst1, 6, src1, 100); // writes 0 to r1 and 6 characters
                                            // 'h', 'e', 'l', 'l', 'o', '\0' to dst1
 
    char dst2[5], src2[7] = {'g','o','o','d','b','y','e'};
    int r2 = strncpy_s(dst2, 5, src2, 7); // copy would overflow the destination array.
                                          // Writes nonzero to r2 and '\0' to dst2[0]
 
    char dst3[5];
    int r3 = strncpy_s(dst3, 5, src2, 4); // writes zero to r3 and the 5 characters
                                          // 'g', 'o', 'o', 'd', '\0' to dst3 
#endif
}
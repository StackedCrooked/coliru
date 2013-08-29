
#include <stdint.h>
#include <stdio.h>

size_t print_u64_commas(uint64_t x,size_t margin){
    //  Prints the decimal representation of x with comma separators.
    //  It will be aligned to the right in the specified margin size.

    //  Returns the # of characters that are printed.


    const size_t BUFFER_SIZE = 9 * 4 * 4/3 + 3;  //  Max string length
    char str[BUFFER_SIZE];                       //  Buffer for the string

    size_t out = 0;

    //  Large margin, print spaces.
    while (margin >= BUFFER_SIZE){
        printf(" ");
        out++;
        margin--;
    }

    size_t start = BUFFER_SIZE - 1 - margin;
    margin = BUFFER_SIZE - 1;
    str[margin] = '\0';

    //  Zero
    if (x == 0)
        str[--margin] = '0';

    //  Write the digits
    size_t c = 0;
    while (x != 0){
        size_t digit = (size_t)(x % 10);
        x /= 10;
        if (c == 3){    //  Write comma
            c = 0;
            str[--margin] = ',';
        }
        c++;
        str[--margin] = (char)digit + '0';
    }

    while (margin > start)
        str[--margin] = ' ';
    if (margin > start)
        margin = start;
    char *pstr = str + margin;
    printf(pstr);

    while (*pstr != '\0'){
        out++;
        pstr++;
    }
    return out;
}

int main(){

    print_u64_commas(1000           ,20);   printf("\n");
    print_u64_commas(123456         ,20);   printf("\n");
    print_u64_commas(65198165132    ,20);   printf("\n");
    print_u64_commas(987198048153   ,20);   printf("\n");

}


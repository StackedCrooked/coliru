#include <stdio.h>
#include <stdbool.h>

#define ERROR_T(Err,Res) Either##Err##Res

#define ERROR_T_DEF(Err,Res) \
struct ERROR_T(Err,Res) { \
    bool failed; \
    union { \
        Err error; \
        Res result; \
    }; \
};

typedef const char * String;

ERROR_T_DEF(String, int)

#define EITHER(a,b) struct ERROR_T(a,b)
#define LEFT(a) { .failed = true, .error = a }
#define RIGHT(a) { .failed = false, .result = a }

//--------------------------------------------------------------------
// END OF BOILERPLATE
//--------------------------------------------------------------------

EITHER(String, int) divBy2 (int a) {
    if (a % 2 != 0)
        return (EITHER(String,int))LEFT("A number is odd");
    else
        return (EITHER(String,int))RIGHT(a / 2);
}

void printEither(EITHER(String, int) e) {
    if (e.failed) {
        printf("%s\n", e.error);
    } else {
        printf("%d\n", e.result);
    }
}

int main () { 
    printEither(divBy2(10));
    printEither(divBy2(9));
}


#include <stdio.h>
#include <stdlib.h>

int add(int a, int b);

typedef struct { int num1; int num2; char *name; } Object;
typedef struct { Object x; int(*add)(int, int);  } ClassRandom;

int add(int a, int b){
    int result = a + b;   
    return result;
}

typedef struct {
    char *key;
    int *value;
} Aa;

int main(){    
    ClassRandom R;
    
    R.add = add;
    R.x.num1 = 234;
    R.x.num2 = 56;
    R.x.name = "Standard Galactic";
    
    
    Aa z;
    z.key = (char*)malloc(sizeof(char) * 200);
    z.key
    int (*fn)(int, int) = add;
    printf("%s World.\n", R.x.name);
    printf("%i and %i = %i", R.x.num1, R.x.num2, fn(R.x.num1, R.x.num2));
    
    return 0;
}


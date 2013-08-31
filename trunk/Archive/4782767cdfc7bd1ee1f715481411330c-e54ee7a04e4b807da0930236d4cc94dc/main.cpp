#include <stdio.h>

int summ (int a, int b){
    return a + b;
}

int diff (int a, int b){
    return a - b;
}

int prod (int a, int b){
    return a * b;
}

int ratio (int a, int b){
    return a / b;
}

int summ3 (int a, int b, int c){
    return a + b + c;
}

typedef int(*Func)(...);
Func func[5] = {(Func)summ, (Func)diff, (Func)prod, (Func)ratio, (Func)summ3};

int main(){

    
    printf("summ %d\ndiff %d\nprod %d\nratio %d\nsumm3 %d", func[0](1,2), func[1](1,2), func[2](1,2), func[3](1,2), func[4](1,2,3));
}

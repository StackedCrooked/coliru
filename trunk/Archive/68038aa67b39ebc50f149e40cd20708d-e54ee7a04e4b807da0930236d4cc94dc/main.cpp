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

int(*func[4])(int, int) = {summ, diff, prod, ratio};

int main(){

    
    printf("summ %d\ndiff %d\nprod %d\nratio %d", func[0](1,2), func[1](1,2), func[2](1,2), func[3](1,2));
}

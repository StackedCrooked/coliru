#include <stdio.h>
#include <vector>

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

std::vector<int(*)(int, int)> vector;

int main(){
    vector.push_back(&summ);
    printf("summ %d", vector.at(0)(1,2));
}

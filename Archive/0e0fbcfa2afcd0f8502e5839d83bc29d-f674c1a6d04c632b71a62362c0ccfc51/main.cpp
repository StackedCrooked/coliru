#include <stdio.h>
#include <map>

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

std::map<char*,int(*)(int, int)> vector;

int main(){
    vector.insert(std::pair<char*,int(*)(int, int)>("Func",&summ));
    printf("summ %d", vector.at("Func")(1,2));
}

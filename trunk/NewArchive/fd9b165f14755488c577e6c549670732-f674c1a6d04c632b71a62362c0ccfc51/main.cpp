#include<iostream>
using namespace std;
struct S {
    S() :x() {} //this line is new
    S(int i) { this->x = i;}
    ~S(){}
    int x;
    static const int sci = 200;
    int y = 999; 
};
int main(){
    S *ps = new S(300);
    ps->x = 400;

    S s;
    s.x = 500;
}
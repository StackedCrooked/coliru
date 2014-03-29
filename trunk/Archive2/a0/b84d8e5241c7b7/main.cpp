#include <iostream>
using namespace std;

class A;
typedef double (A::*f)(double);
double doSomething(double i, f p, A* ap);

class A {
public:

    A(double x) : number(x) {
    }

    double times(double i) {
        return ::doSomething(i, &A::multiply, this);
    } //calles the global function and gives a member function as parameter

    double multiply(double i) {
        return number*i;
    }
private:
    double number;
};

double doSomething(double i, double (A::*fp)(double), A* ap) {
    return (ap->*fp)(i);
}

int main() {

    A obj(5.0);
    cout << obj.times(3.5) << endl;

    return 0;
}
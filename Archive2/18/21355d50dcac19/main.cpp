#include <iostream>
#include <array>

using namespace std;

const int N = 1000;

class MyClass{
    // constructor here, contains 1 int and 5 floats
};

typedef array<array<MyClass,N>,N> ClassArray;

int main(){
    cout << "Beginning" << endl;
    ClassArray A;
    cout << A.size() << endl;
    //operations
}
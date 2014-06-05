 #include <iostream>
 
 using namespace std;
 
 struct A { void f(int) { cout << "Fi" << endl; } };
 struct B { void f(float) { cout << "Ff" << endl; } };
 
 struct C : A, B
 {};
 
 int main()
 {
    C().f(0);
 }
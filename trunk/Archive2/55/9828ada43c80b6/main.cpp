 #include <iostream>
 
 using namespace std;
 
 void f(int) { cout << "Fi" << endl; }
 void f(float) { cout << "Ff" << endl; }
 
 struct A
 {
        void f(int) { cout << "Fi" << endl; }
        void f(float) { cout << "Ff" << endl; }
 };
 
 int main()
 {
    f(0);
    
    A().f(0);
 }
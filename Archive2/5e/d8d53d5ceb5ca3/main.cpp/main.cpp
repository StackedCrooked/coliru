#include <iostream>
using namespace std;

class Empty{};

template<class T> void f (const T* t)          {  cout << "template<class T> void f (const T* t) " << endl; }
template<class T> void f (T* t)          {  cout << "template<class T> void f (T* t)" << endl; }
template<class T> void f (T t)          {  cout << "template<class T> void f (T t)" << endl; }


void test_1() {
    
 int integer=0;
 f(integer); // T = 'int'
   
 const int integer_const = 0;
 f(integer_const);  // T = 'int'
 
 const int& integer_const_ref = integer;
 f(integer_const_ref); //  // T = 'int'
 
 const int& integer_ref = integer;
 f(integer_ref);  // T = 'int'
 
 const int* integer_const_ptr = &integer;
 f(integer_const_ptr);  // T = 'const int*'
 
 int* integer_ptr = &integer;
 f(integer_ptr);  // T = 'int*'
   
}

int main() { 
    test_1();
}
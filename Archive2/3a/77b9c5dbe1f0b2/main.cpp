//ref-qualifiers for *this
//http://stackoverflow.com/questions/8610571/what-is-rvalue-reference-for-this?lq=1

struct S {
  S& operator ++() {return *this;}
  S* operator &()  {return this;} 
};


int main() {
    S() = S();      // rvalue as a left-hand-side of assignment!
    S& foo = ++S(); // oops, dangling reference
    &S();           // taking address of rvalue...
    
    //S& foo2 = S();  //but  error: invalid initialization of non-const reference of type 'S&' from an rvalue of type 'S'
    
    return 0;
}
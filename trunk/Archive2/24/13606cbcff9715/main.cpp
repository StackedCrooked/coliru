struct X {

};
struct Y {

};
void foo() {
    Y X; // Create an object of type Y called X.
    X(); // Create a temporary object of type X.
}

/* Give Y an operator() */
void operator()(Y& receiver) {
    
}
void bar() {
   Y X; // Create an object of type Y called X.  
   X(); // Call `operator()` using X as its argument
}

int main()
{
    foo(); bar();
}
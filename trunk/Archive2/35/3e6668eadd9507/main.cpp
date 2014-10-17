struct A
{
    int sum(int val) { return val+foo; };
    static int foo;  
};

//auto A::foo=42; -std=c++11 OK
//A::foo=42; //error: C++ requires a type specifier for all declarations
int A::foo=42; //repetition of type int, Why?

 int main()
 {
    A myA; //Do Something with A
    int sum = myA.sum(5); //Do Something with A
    return sum;
 };
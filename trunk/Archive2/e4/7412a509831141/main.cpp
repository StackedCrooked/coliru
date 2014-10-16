struct A
{
    int sum(int val) { return val+foo; };
    static int foo;  
};

//auto A::foo=42; -std=c++11 OK
A::foo=42;

 int main()
 {
    A myA;
    int sum = myA.sum(5);
    return 0;
 };
 


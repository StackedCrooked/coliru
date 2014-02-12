#include <type_traits>
 
struct S {
    double operator()(char, int&);
    float operator()(int);
};
 
struct C {
    double Func(char, int&);
};
 
 
 #include <iostream>
#include <type_traits>

double f(int i)
{
        return i+0.1;
}

struct F
{
        public:
        int test(int i) { return i+0.1; }
};

int main()
{
    // the result of invoking S with char and int& arguments is double
    std::result_of<S(char, int&)>::type f = 3.14; // f has type double
    static_assert(std::is_same<decltype(f), double>::value, "");
 
    // the result of invoking S with int argument is float
    std::result_of<S(int)>::type d = 3.14; // f has type float
    static_assert(std::is_same<decltype(d), float>::value, "");
 
    // result_of can be used with a pointer to member function as follows
    std::result_of<decltype(&C::Func)(C, char, int&)>::type g = 3.14;
    static_assert(std::is_same<decltype(g), double>::value, "");

   std::result_of<decltype(&F::test)(F, int)>::type x = 3.14;
   3
   std::cout << x << std::endl;
   
}
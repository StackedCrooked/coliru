#include <iostream>
template<typename T>struct number;

     template<typename T> number<T> gcd(number<T> x, number<T> y) 
    { x;y;std::cout << "in function<T>" <<std::endl; return number<T>(0);}
template<typename T>
struct number
{
    number(int){}
    friend number gcd(number x, number y) 
    { x;y;std::cout << "in function" <<std::endl; return number(0);} // definition within
                                                         // a class template
     friend number<T> gcd<T>(number<T> x, number<T> y) ;
};
// unless a matching declaration is provided gcd is an invisible (except through ADL)
// member of this namespace
void g() {
    number<double> a(3), b(4);
    a = gcd<double>(a,4); // finds gcd because number<double> is an associated class,
                  // making gcd visible in its namespace (global scope)
  b = gcd(a,4); // Error; gcd is not visible
}
int main()
{
    g();
    std::cout << "Test\n"; // There is no operator<< in global namespace, but ADL
                           // examines std namespace because the left argument is in
                           // std and finds std::operator<<(std::ostream&, const char*)
    operator<<(std::cout, "Test\n"); // same, using function call notation
 
    // however,
 //   cout << std::endl; // Error: 'endl' is not declared in this namespace.
                       // This is not a function call to endl(), so ADL does not apply
 
    endl(std::cout); // OK: this is a function call: ADL examines std namespace
                     // because the argument of endl is in std, and finds std::endl
 
 //   (endl)(std::cout); // Error: 'endl' is not declared in this namespace.
                       // The sub-expression (endl) is not a function call expression
}
#include <iostream>
#include <string>
#include <type_traits>


namespace MyNS {        
    
    // Forward declaration to to_string function.
    template<typename T>
    std::string to_string(const T& t);
                
    // Color enum (weakly typed)
    enum Color : int { Red, Blue, Green };
        
    // Integer wraper (implicit constructor and conversion operator)
    struct Integer {
        Integer(int n = 0) : n(n) {}
        operator int() const { return n; }
        int n;
    };
    
    namespace Detail {
        
        template<typename T> struct identity{ typedef T type; };
        
        std::string to_string_impl(identity<int>, int n) {
            return std::to_string(n);
        }
        
        std::string to_string_impl(identity<short>, short s) {
            return to_string<int>(s);
        }
        
        std::string to_string_impl(identity<Color>, Color c) {
            switch (c) {
                case Red  : return "Color(Red)";
                case Green: return "Color(Green)";
                case Blue : return "Color(Blue)";
                default   : return "Color()";
            }
        }
        
        std::string to_string_impl(identity<Integer>, const Integer& i) {
            return "Integer(" + to_string(i.n) + ')';
        }
        
    } // namespace Detail
    
    // Converts objects to string.
    template<typename T>
    std::string to_string(const T& t) {
        return to_string_impl(Detail::identity<T>{}, t);
    }

} // namespace MyNS



int main()
{
    using namespace MyNS;
    std::cout << "Using type deduction" << std::endl;
    std::cout << '\t' << to_string(1) << std::endl;
    std::cout << '\t' << to_string(Integer{2}) << std::endl;
    
    std::cout << "\nUsing explicit type argument" << std::endl;
    std::cout << '\t' << to_string<Integer>(3) << std::endl;
    std::cout << '\t' << to_string<int>(Integer{4}) << std::endl;
}


    #include <iostream>
    #include <type_traits>
    using namespace std;
    
    template<typename T>
    struct Recursive
    {
        using cycle = struct X : Recursive<X> {};
    };
    
    
    int main() 
    {
        Recursive<int> x;
        static_assert(std::is_same<decltype(x)::cycle, decltype(x)::X>::value, "");
    	return 0;
    }
    #include <iostream>
    #include <type_traits>
    using namespace std;
    
    template<typename T>
    struct Cycle
    {
        using self_type = T;
    };
    
    template<class T>
    struct Recursive: Cycle< Recursive<T> > {};
    
    
    int main() 
    {
        Recursive<int> x;
        static_assert(std::is_same<decltype(x)::self_type, Recursive<int>>::value, "");
    	return 0;
    }
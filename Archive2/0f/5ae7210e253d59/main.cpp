#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

template< typename T > 
struct supports_optimised_implementation{ 
    static const bool value = false;
};

template<> 
struct supports_optimised_implementation< void >{ 
    static const bool value = true; 
};
template< bool b > 
struct algorithm_selector { 
    template< typename T > 
    static void implementation( T& object ) 
    { 
        //implement the alorithm operating on "object" here 
    } 
};

template<> 
struct algorithm_selector< true > { 
    template< typename T > 
    static void implementation( T& object ) { 
        object.optimised_implementation(); 
    } 
};

template< typename T > 
void algorithm( T& object ) { 
     algorithm_selector< supports_optimised_implementation< T >::value >::implementation(object); 
}

class ObjectB { 
public: 
    void optimised_implementation() { 
        //... 
    }
};

class ObjectA { 
public: 
    //void optimised_implementation() { 
        //... 
    //}
};

template<> 
struct supports_optimised_implementation< ObjectB > { 
    static const bool value = true; 
};
int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    ObjectA a; 
    algorithm( a ); 
    // calls default implementation 
    ObjectB b; 
    algorithm( b ); 
    // calls 
    // ObjectB::optimised_implementation(); 
    return 0;     
}

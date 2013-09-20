#include <iostream>
#include <vector>

template<typename T>
class Vector {
public:
    std::vector<T> data;

    template<class mapFunction>
    // Below: use C++11 trailing return type
    auto map(mapFunction function) -> Vector<decltype(function(std::declval<T>()))>
    //                                       |                                   |
    {   //                                   |                                   |
        //                                   \-----------------------------------/
        //                                          |
        //                                          |
        //                 /-----------------------------------\
        //                 |                                   |
        using ReturnType = decltype(function(std::declval<T>()));
                                 
        auto size = data.size(); 
        Vector<ReturnType> result;
        result.data.reserve(size);

        for(std::size_t i = 0; i < size; i++)
        {
           result.data.push_back(function(data[i]));
        }

        return result;
    }
};

int main() {
    Vector<int> v;
    for(int i = 0; i < 10; ++i) {
        v.data.push_back(i);
    }
    
    auto newV = v.map([](int i) -> float {
        return (i * 2.0f) + 0.5f;       // Multiply by 2 and add 0.5
    });
    
    for(auto e : newV.data) {
        std::cout << e << std::endl;
    }
}

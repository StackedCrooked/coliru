#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <list>



namespace tesla {
    
    template<typename T, size_t first, size_t... rest>
    struct multi_array {
        enum { dims = sizeof...(rest) };
        typedef std::array< typename multi_array<T, rest...>::type, first > type;
    };
    
    template<typename T, size_t first>
    struct multi_array<T,first>{
        enum { dims = 1 };
        typedef std::array<T,first> type;
    };
    
    template <typename T, std::size_t... ds> 
    using Array = typename multi_array<T, ds ...>::type;
    
};

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {

    os << "{";
    for(int i = 0; i < N - 1; i++)
        os << arr[i] << ", ";
    os << arr[N - 1];
    os << "}";
    return os;
}



template<typename T, size_t N>
void init(std::array<T,N>& arr) {
    for(int i = 0; i < arr.size(); i++)
        for(int j = 0; j < arr[i].size(); j++)
            for(int k = 0; k < arr[i][j].size(); k++)
                arr[i][j][k] = i + j + k;
}






int main()
{
    
using tesla::Array;
using std::endl;
using std::cout;
    
    Array<int,2,3,4> arr1;
    Array<int,3,4> arr2 = {};
        
    init(arr1);
    arr2[0] = arr1[0][0];
    arr1[1][2][0] = 9;
    std::cout << arr2 << std::endl;
    std::cout << arr1 << std::endl;
    
}



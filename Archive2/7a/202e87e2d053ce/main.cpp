#include <type_traits>
#include <cstddef>
#include <string>
#include <iostream>

struct field
{
    template<typename TDataType, typename
            std::enable_if<std::is_fundamental<TDataType>::value
                           && !std::is_same<TDataType, std::nullptr_t>::value
                           && !std::is_same<TDataType, void>::value
                          , int>::type = 0
            >
    void set_data(TDataType data, size_t index = 0)
    {
        std::cout << "set_data fundamental" << std::endl;
    }
    
    template<typename TDataType, typename
            std::enable_if<std::is_same<std::string const &, TDataType>::value
                           || std::is_same<char const *, TDataType>::value
                          , int>::type = 0
            >
    void set_data(TDataType data, size_t index = 0)
    {
        std::cout << "set_data string" << std::endl;
    }
};

int main()
{
    field f;
    int x = 10;
    f.set_data(x);
}

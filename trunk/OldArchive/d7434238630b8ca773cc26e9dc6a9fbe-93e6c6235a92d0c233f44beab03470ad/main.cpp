#include <typeinfo>
#include <iostream>

using namespace std;

template<typename FirstDataType>
void OutputSizes() // We're called when there's no template arguments
                   // left in the pack
{
    std::cout << typeid(FirstDataType).name() << ": " << sizeof(FirstDataType) << std::endl;
}

template <typename FirstDatatype, typename SecondDataType, typename... DatatypeList>
void OutputSizes()
{
    std::cout << typeid(FirstDatatype).name() << ": " << sizeof(FirstDatatype) << std::endl;
    std::cout << typeid(SecondDataType).name() << ": " << sizeof(SecondDataType) << std::endl;
    OutputSizes<DatatypeList...>();
}


int main()
{
    OutputSizes<char, int, long int>();
    return 0;
}
#include <vector>
#include <map>
#include <iostream>

enum class EContainnerType
{
    EContainnerType_Normal,
    EContainnerType_OR,
    EContainnerType_AND
};

// Base declaration
template <EContainnerType, template <typename...> class ContainerType>
struct ConditionContainnerType
{
    void foo() { std::cout << "base" << std::endl; }
};

// Partial specialization for std::vector
template <>
struct ConditionContainnerType<EContainnerType::EContainnerType_OR, std::vector>
{
    void foo() { std::cout << "vector" << std::endl; }
};  

// Partial specialization for std::map
template <>
struct ConditionContainnerType<EContainnerType::EContainnerType_AND, std::map>
{
    void foo() { std::cout << "map" << std::endl; }
};  

int main()
{
    ConditionContainnerType<EContainnerType::EContainnerType_OR, std::vector> x1;
    x1.foo();
    
    ConditionContainnerType<EContainnerType::EContainnerType_AND, std::map> x2;
    x2.foo();
}

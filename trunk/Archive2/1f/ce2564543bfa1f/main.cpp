#include <vector>
#include <iostream>

template <typename... Args>
struct MyContainer
{
};

enum class EContainnerType
{
  EContainnerType_Normal,
  EContainnerType_OR,
  EContainnerType_AND
};

//base declaration
template <EContainnerType, typename ContainerType, typename... Args>
struct ConditionContainnerType
{
    void foo() { std::cout << "base" << std::endl; }
};

//Partial Specialization
template <template <typename...> class ContainerType, typename... Args>
struct ConditionContainnerType<EContainnerType::EContainnerType_OR, ContainerType<Args...>, Args...>
{
    void foo() { std::cout << "specialized" << std::endl; }
};  

int main()
{
    ConditionContainnerType<EContainnerType::EContainnerType_AND, MyContainer<int>, int> x1; // base, AND does not match OR
    x1.foo();
    
    ConditionContainnerType<EContainnerType::EContainnerType_OR, MyContainer<int>, int> x2; // specialized, OR and parameter pack matches
    x2.foo();
    
    ConditionContainnerType<EContainnerType::EContainnerType_OR, MyContainer<float>, int> x3; // base, OR matches, but parameters packs do not
    x3.foo();
    
    return 0;
}

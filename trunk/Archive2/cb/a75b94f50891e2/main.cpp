#include <iostream>
#include <type_traits>
#include <memory>
#include <string>
#include <vector>
using namespace std;

template<typename T>
auto automaticDeducedReturnType(T&& a, T&& b)
{
    return a+b;
}

vector<int> v{1,2,3,4};

decltype(auto) getValue(size_t index)
{
    return v[index];
}

auto getValueByAuto(size_t index)
{
    return v[index];
}

template<typename T>
constexpr T pi = T(3.1415926535897932385);

int main()
{
    // generic lambdas 
    auto printer = [](const auto& val) {
       cout << val << endl;
    };
   
    printer(10);
    printer("hello");
   
    // initialized lambda capture 
    unique_ptr<int> ptr {new int{10}};
    auto clojure = [ptr = move(ptr)]{
        cout << *ptr << endl;  
    };
    if (ptr)
     cout << "ops...move didn't work..." << endl;
     
    // single quotation mark as a digit separator
    auto digits = 1'000'000;
    cout << digits << endl;
    
    // return type deduction
    cout << automaticDeducedReturnType(1, 2) << endl;
    cout << automaticDeducedReturnType(string{"ciao"}, string{"oooo"}) << endl;
    
    // decltype(auto)
    cout << std::is_same<int&, decltype(getValue(0))>::value << endl;
    cout << std::is_same<int, decltype(getValueByAuto(0))>::value << endl;
    
    // 
}


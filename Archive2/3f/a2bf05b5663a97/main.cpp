#include <iostream>
#include <future>

class TestCBClass {
public:
    TestCBClass(const int& rValue = 1)
        : mValue(rValue) {
    }
    
    void testCBEmpty(void) {
        std::cout << "testCBEmpty()" << std::endl;
    }
    int testCBArgRet(const int& rArg) {
        std::cout << "testCBArgRet(" << rArg << ")" << std::endl;
        mValue = rArg;
        return 1;
    }
    static void testCBEmptyStatic(void) {
        std::cout << "testCBEmptyStatic()" << std::endl;
    }
    
private:
    int mValue;
};

template <typename T>
struct return_type;
template <typename R, typename... Args>
struct return_type<R(*)(Args...)> { using type = R; };
template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...)> { using type = R; };
template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const> { using type = R; };
template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) volatile> { using type = R; };
template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const volatile> { using type = R; };
template <typename T>
using return_type_t = typename return_type<T>::type;

int main()
{
    TestCBClass t;   
    
    std::future<return_type_t<decltype(&TestCBClass::testCBArgRet)>> a = std::async(&TestCBClass::testCBArgRet, t, 1);
    std::future<return_type_t<decltype(&TestCBClass::testCBEmpty)>> b = std::async(&TestCBClass::testCBEmpty, t);
    std::future<return_type_t<decltype(&TestCBClass::testCBEmptyStatic)>> c = std::async(&TestCBClass::testCBEmptyStatic);
}

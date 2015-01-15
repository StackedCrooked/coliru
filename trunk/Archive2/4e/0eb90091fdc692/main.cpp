#include <string>
#include <type_traits>

using MyBigType = std::string;

class MyClass {
  public:
    template <typename T>
    typename std::enable_if<std::is_convertible<T, MyBigType>::value, void>::type
    f(T&& a, int id)
    {
        this->a_ = std::forward<T>(a);
    }
  private:
    std::string a_;
};
    
int main() {
    MyClass c;
    c.f(std::string("Hello"), 1);
    c.f("Hello", 1);
    //c.f(2, 3); // compile-time error
}

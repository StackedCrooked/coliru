#include <utility>
template <typename... Args>
void bar(Args&&... arga){}

template <typename... Args>
void foo(Args&&... args)
{
    bar(std::forward<Args>(args)...);      // variant 1
    bar(std::forward<Args...>(args...));   // variant 2

    // EDIT the above is a fixed version, the initial incorrect version was
    // bar(std::forward<Args>(args...));      // variant 1
    // bar(std::forward<Args...>(args...));   // variant 2

}

int main(){
    foo();
}
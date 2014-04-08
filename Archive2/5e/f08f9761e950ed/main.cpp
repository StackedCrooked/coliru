#include <memory>
#include <iostream>
#include <functional>
#include <utility>
#include <type_traits>

using namespace std;

// MAKE_SHARED IMPLEMENTATION
// edited version of http://stackoverflow.com/a/13512344/1942027
// with parts of http://stackoverflow.com/a/22927217/1942027 to allow polymorphic behavior without virtual destructor.

template <typename T, typename... Args>
std::unique_ptr<T, void(*)(void*)> make_unique_helper(std::false_type, Args&&... args) {
  return std::unique_ptr<T, void(*)(void*)>(new T(std::forward<Args>(args)...), [](void*t){delete (T*)t;} );
}

template <typename T, typename... Args>
std::unique_ptr<T, void(*)(void*)> make_unique_helper(std::true_type, Args&&... args) {
   static_assert(std::extent<T>::value == 0,
       "make_unique<T[N]>() is forbidden, please use make_unique<T[]>().");

   typedef typename std::remove_extent<T>::type U;
   return std::unique_ptr<T, void(*)(void*)>(new U[sizeof...(Args)]{std::forward<Args>(args)...}, [](void*t){delete [] (T*)t;} );
}

template <typename T, typename... Args>
std::unique_ptr<T, void(*)(void*)> make_unique(Args&&... args) {
   return make_unique_helper<T>(std::is_array<T>(), std::forward<Args>(args)...);
}

// YOUR CODE

class Base
{
public:
    virtual void Fun() = 0;
};


class Derived : public Base
{
public:

    ~Derived()
    {
        cout << "Derived::~Derived\n";
    }

    void Fun()
    {
        cout << "Derived::Fun\n";
    }
};


int main()
{
    unique_ptr<Base, void(*)(void*) > pB = make_unique<Derived>();
    pB->Fun();
}
#include <memory>
#include <type_traits>

template <typename T>
class Base {};

class Derived : public Base<int> {};

namespace detail
{
    template<typename T>
    void deducer(Base<T>);

    bool deducer(...);
}

template <typename D, typename std::enable_if<
    std::is_same<
        decltype(detail::deducer(std::declval<D>())),
        void
        >::value>::type* = nullptr>
void func(std::shared_ptr<D> ptr)
{
    // ...
}

int main(int argc, char* argv[])
{
   std::shared_ptr<Base<int>> myfoo(std::shared_ptr<Derived>(new Derived));
   func(myfoo);
   func(std::shared_ptr<Derived>(new Derived));
   func(std::shared_ptr<Base<int>>(new Base<int>()));
}

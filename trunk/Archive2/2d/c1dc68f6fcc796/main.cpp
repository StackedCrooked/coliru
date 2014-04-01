#include <memory>
#include <type_traits>

template<typename T>
class A{};

class B : public A<double>{};

class C {};

namespace detail 
{
    template<typename T>
    void deducer(A<T>);
    
    bool deducer(...);
}


template<typename T, typename std::enable_if<
                        std::is_same<
                            decltype(detail::deducer(std::declval<T>())),
                            void
                            >::value>::type* = nullptr>
void doSmth(std::shared_ptr<T> ptr)
{
//    std::shared_ptr<A<> > casted = ptr;
}

int main(int argc, char* argv[])
{
    std::shared_ptr<A<double> > ptrA = std::make_shared<A<double> >();
    std::shared_ptr<B> ptrB = std::make_shared<B>();
    std::shared_ptr<C> ptrC = std::make_shared<C>();
    
    doSmth(ptrA);
    doSmth(ptrB);
//    doSmth(ptrC); compile error, as assumed
    
}
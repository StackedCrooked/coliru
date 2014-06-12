
#include <iostream>


// Using Score<N> to indicate overload resolution score?
// Higher N means higher preference.
template<int N> struct Score : Score<N - 1> {};
template<> struct Score<0> {};



template<typename T>
auto foo_impl(T&& t, Score<10>) -> decltype(t.toString(), void())
{
    std::cout << t.toString() << std::endl;
}

template<typename T>
auto foo_impl(T&& t, Score<10>) -> decltype(t->toString(), void())
{
    std::cout << t->toString() << std::endl;
}

template<typename T>
auto foo_impl(T&& t, Score<9>) -> decltype(t.getId(), void())
{
    std::cout << t.getId() << std::endl;
}

template<typename T>
auto foo_impl(T&& t, Score<9>) -> decltype(t->getId(), void())
{
    std::cout << t->getId() << std::endl;
}

template<typename T>
auto foo_impl(T&& t, Score<8>) -> decltype(std::to_string(*t), void())
{
    std::cout << std::to_string(*t) << std::endl;
}

template<typename T>
auto foo_impl(T&& t, Score<7>) -> decltype(std::to_string(std::forward<T>(t)), void())
{
    std::cout << std::to_string(std::forward<T>(t)) << std::endl;
}


template<typename T>
auto foo_impl(T&& t, Score<6>) -> decltype(std::declval<std::ostream&>() << t, void())
{
    std::cout << t << std::endl;
}


template<typename T>
void foo(T&& t)
{
    foo_impl(std::forward<T>(t), Score<100>());
}




int main()
{
    struct Item
    {
        std::string toString() const { return "Item"; }
    };
    
    struct Object
    {
        std::string getId() const { return "Object::id"; }
    };
    
    struct ItemObject : Item, Object
    {
        std::string toString() const { return "ItemObject"; }
        std::string getId() const { return "ItemObject::id"; }
    };
    
    foo(Item());
    foo(new Item());
    foo(Object());
    foo(new Object());
    foo(ItemObject());
    foo(2L);
}
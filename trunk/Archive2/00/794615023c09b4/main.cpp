#include <iostream>
#include <sstream>
#include <utility>

namespace detail
{
    template <class T>
    void print(std::ostream& stream, const T& item)
    {
        stream << item;
    }

    template <class Head, class... Tail>
    void print(std::ostream& stream, const Head& head, Tail&&... tail)
    {
        detail::print(stream, head);
        detail::print(stream, std::forward<Tail>(tail)...);
    }
}

template <class... Args>
void print(std::ostream& stream, Args&&... args)
//note: candidate function not viable: requires 3 arguments, but 4 were provided
{
    detail::print(stream, std::forward<Args>(args)...);
}

int main()
{
    print(std::cout, "The answer is ", 42, std::endl<char, std::char_traits<char>>, "Yay");
    //error: no matching function for call to 'print'
}
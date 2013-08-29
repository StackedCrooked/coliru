#include <iostream>
namespace Utils {
template<typename T>
struct Link
{
    Link(T&& val) : val(std::forward<T>(val)) {}

    T val;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Link<T>& link)
{
    out << "Link(" << link.val << ")";
    return out;
}

template<typename T>
auto MakeLink(T&& val) -> Link<T>
{
    return {std::forward<T>(val)};
}


template<typename Any>
constexpr auto RemoveLinks(const Any& any) -> const Any&
{
    return any;
}

template<typename T>
constexpr auto RemoveLinks(const Link<T>& link) -> decltype(RemoveLinks(link.val))
{
    return RemoveLinks(link.val);
}

} /* Utils */

int main()
{
    int k = 10;

    auto link = MakeLink(Utils::MakeLink(k));

    std::cout << link << std::endl;
    std::cout << Utils::RemoveLinks(link) << std::endl;
}

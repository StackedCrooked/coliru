#include <initializer_list>

struct foo {
    template<typename T>
    void at(T&&) = delete;

    template<typename T>
    void at(T&&) const = delete;

    void at(std::initializer_list<int> l)
    { static_cast<foo const&>(*this).at(l); }

    void at(std::initializer_list<int>) const {}
};

int main()
{
    foo {}.at({ 0 });
}
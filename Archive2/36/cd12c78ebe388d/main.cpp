#include <iostream>

namespace detail {
    template<class...>
    struct make_void { using type = void; };
    
    template<class... Ts>
    using void_t = typename make_void<Ts...>::type;
    
    template<class T, class = void>
    struct has_size_member : std::false_type { };
    
    template<class T>
    struct has_size_member<T, decltype(std::declval<T&>().size(), void())>
        : std::true_type { };
}

template <class T>
struct MyHelper
{
    size_t size() const { return sizeof(T); }
    void print(std::ostream& out) const { out << "(" << get_size(detail::has_size_member<T>()) << ")"; }
private:
    std::size_t get_size(std::true_type) const
    { return static_cast<T const&>(*this).size(); }
    
    std::size_t get_size(std::false_type) const
    { return sizeof(T); }
};

struct X : MyHelper<X>
{
    size_t size() const { return 24; }
};

int main()
{
    MyHelper<X> v;
    v.print(std::cout);
}
#include <vector>
#include <set>
#include <string>

namespace traits
{
    template <typename Container, typename Enable = void>
        struct add_at_end;

    template <typename... TAs>
        struct add_at_end<std::vector<TAs...> > 
        {
            using Container = std::vector<TAs...>;

            template <typename... CtorArgs>
            static void apply(Container& container, CtorArgs&&... args) {
                container.emplace_back(std::forward<CtorArgs>(args)...);
            }
        };

    template <typename... TAs>
        struct add_at_end<std::set<TAs...> > 
        {
            using Container = std::set<TAs...>;

            template <typename... CtorArgs>
            static void apply(Container& container, CtorArgs&&... args) {
                container.insert(container.end(), { std::forward<CtorArgs>(args)...});
            }
        };

    template <typename... TAs>
        struct add_at_end<std::basic_string<TAs...> > 
        {
            using Container = std::basic_string<TAs...>;

            template <typename... CtorArgs>
            static void apply(Container& container, CtorArgs&&... args) {
                container.insert(container.end(), { std::forward<CtorArgs>(args)...});
            }
        };
}

template <typename Container, typename... CtorArgs>
    void add_to(Container& container, CtorArgs&&... args) {
        traits::add_at_end<Container>::apply(container, std::forward<CtorArgs>(args)...);
    }

int main()
{
    using X = std::pair<int, std::string>;

    std::vector<X> v;
    std::set<X>    s;
    std::wstring   wstr;
    std::string    str;

    add_to(v, 12, "hello");
    add_to(s, 42, "world");
    add_to(wstr, L'!');
    add_to(str, '?');
}


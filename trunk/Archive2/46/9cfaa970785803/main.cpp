#include <vector>
#include <set>

namespace traits
{
    template <typename Container, typename Enable = void>
        struct emplacer;

    template <typename... TAs>
        struct emplacer<std::vector<TAs...> > 
        {
            using Container = std::vector<TAs...>;

            template <typename... CtorArgs>
            static void apply(Container& container, CtorArgs&&... args) {
                container.emplace_back(std::forward<CtorArgs>(args)...);
            }
        };

    template <typename... TAs>
        struct emplacer<std::set<TAs...> > 
        {
            using Container = std::set<TAs...>;

            template <typename... CtorArgs>
            static void apply(Container& container, CtorArgs&&... args) {
                container.insert(container.end(), { std::forward<CtorArgs>(args)...});
            }
        };
}

template <typename Container, typename... CtorArgs>
    void add_to(Container& container, CtorArgs&&... args) {
        traits::emplacer<Container>::apply(container, std::forward<CtorArgs>(args)...);
    }

#include <string>

int main()
{
    using X = std::pair<int, std::string>;

    std::vector<X> v;
    std::set<X> s;

    add_to(v, 12, "hello");
    add_to(s, 42, "world");
}


#include <iostream>
#include <map>
#include <memory>

struct base {
    virtual
    ~base() { }
    
    virtual void
    shout() = 0;
};

struct first : base {
    void
    shout() override {
        std::cout << "first\n";
    }
};

struct second : base {
    void 
    shout() override {
        std::cout << "second\n";
    }
};

using map_type = std::map<int, std::unique_ptr<base>>;

namespace detail {
    
template <typename...>
struct filler;

template <>
struct filler<> {
    static void
    do_(map_type&, int) { }
};

template <typename T, typename... Ts>
struct filler<T, Ts...> {
    static void
    do_(map_type& m, int key) {
        m.insert(std::make_pair(key, std::unique_ptr<base>{new T}));
        filler<Ts...>::do_(m, key + 1);
    }
};

}

template <typename... Ts>
void
fill_the_thing(map_type& m, int key) {
    detail::filler<Ts...>::do_(m, key);
}

int
main() {
    map_type m;
    fill_the_thing<second, first>(m, 2);
    
    for (auto const& kv : m) {
        std::cout << kv.first << ": ";
        kv.second->shout();
    }
}

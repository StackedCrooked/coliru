//////////////////////////////////////////
// my_any.hpp
#include <memory>
#include <stdexcept>

struct my_any
{
    my_any() = default;
    template <typename T> my_any(T const& v) : _storage(new storage<T>(v)) { }
    my_any(my_any const& other)              : _storage(other._storage? std::move(other._storage->clone()) : nullptr) {}
    
    void swap(my_any& other)               { _storage.swap(other._storage); }
    friend void swap(my_any& a, my_any& b) { a.swap(b); };
    my_any& operator=(my_any other)        { swap(other); return *this; }

    // todo move semantics
private:
    struct storage_base { 
        virtual std::unique_ptr<storage_base> clone() = 0;
        virtual ~storage_base() = default; 
    };
    template <typename T>
    struct storage : storage_base {
        T value;
        explicit storage(T const& v) : value(v) {}
        std::unique_ptr<storage_base> clone() { return std::unique_ptr<storage_base>(new storage<T>(value)); }
    };
    std::unique_ptr<storage_base> _storage;
    template<typename T> friend T      & any_cast(my_any      &);
    template<typename T> friend T const& any_cast(my_any const&);
};

template <typename T> T& any_cast(my_any& a) { 
    if (auto p = dynamic_cast<my_any::storage<T>*>(a._storage.get()))
        return p->value;
    else
        throw std::bad_cast();
}

template <typename T> T const& any_cast(my_any const& a) { 
    if (auto p = dynamic_cast<my_any::storage<T> const*>(a._storage.get()))
        return p->value;
    else
        throw std::bad_cast();
}

//////////////////////////////////////////
// main.cpp
#include <string>
#include <vector>
#include <iostream>

struct Properties {
    Properties(const std::string &s="", const my_any& p={}) 
        : name(s), value(p) {}

    template <typename T> Properties(T n) { value = n; }

    std::string name;
    my_any value;
};

typedef std::vector<Properties> Props;

int main()
{
    Props v;
    v.emplace_back("bye", 42);
    v.emplace_back("vector", v);

    std::cout << "v.size(): "          << v.size()                           << "\n";
    std::cout << "v[0].value: "        << any_cast<int>(v[0].value)          << "\n";
    std::cout << "v[1].value.size(): " << any_cast<Props>(v[1].value).size() << "\n";

    v[0].value = v;

    try {
        std::cout << "v[0].value: " << any_cast<int>(v[0].value) << "\n";
    } catch(std::exception const& e)
    {
        std::cout << e.what() << " exception caught, ok!\n";
    }

    std::cout << "v[0].value.size(): " << any_cast<Props>(v[0].value).size() << "\n";
}

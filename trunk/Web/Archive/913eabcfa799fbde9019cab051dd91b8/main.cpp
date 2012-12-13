#pragma once
#include <typeinfo>
#include <functional>
#include <stdexcept>
#include <iostream>

class any {
public:
    template<typename T>
    explicit any(T object)
    : info{&typeid(T)}
    , value{new T(std::move(object))}
    , deleter{deleter_t<T>{}}
    , cloner{cloner_t<T>{}}
    , mover{mover_t<T>{}} {}

    any(any const& other)
    : info{other.info}
    , value{other.cloner(other.value)}
    , deleter{other.deleter}
    , cloner{other.cloner}
    , mover{other.mover} {}

    any(any&& other)
    : info{other.info}
    , value{other.mover(other.value)}
    , deleter{std::move(other.deleter)}
    , cloner{std::move(other.cloner)}
    , mover{std::move(other.mover)} {}

    template<typename T>
    any& operator=(T object) {
        using std::swap;
        swap(*this, any{object});
        return *this;
    }

    any& operator=(any other) {
        using std::swap;
        swap(*this, other);
        return *this;
    }

    any& operator=(any&& other) {
        using std::swap;
        swap(*this, other);
        return *this;
    }

    ~any() {
        deleter(value);
    }

private:
    template<typename T>
    struct deleter_t {
        void operator()(void* obj) {
            delete static_cast<T*>(obj);
        }
    };

    template<typename T>
    struct cloner_t {
        void* operator()(void* obj) {
            return new T(*static_cast<T*>(obj));
        }
    };

    template<typename T>
    struct mover_t {
        void* operator()(void* obj) {
            return new T(std::move(*static_cast<T*>(obj)));
        }
    };

    std::type_info const* info;
    void* value;
    std::function<void(void*)> deleter;
    std::function<void*(void*)> cloner;
    std::function<void*(void*)> mover;

    friend void swap(any& a, any& b) {
        using std::swap;
        swap(a.info, b.info);
        swap(a.value, b.value);
        swap(a.deleter, b.deleter);
        swap(a.cloner, b.cloner);
        swap(a.mover, b.mover);
    }

    template<typename T>
    friend T const& any_cast(any const& the_any) {
        if (typeid(T) != *the_any.info) throw std::bad_cast{};
        return *static_cast<T*>(the_any.value);
    }

    template<typename T>
    friend T& any_cast(any& the_any) {
        if (typeid(T) != *the_any.info) throw std::bad_cast{};
        return *static_cast<T*>(the_any.value);
    }
};

int main() {
    any foo{42};
    any bar{"Hello, world!"};

    std::cout << any_cast<int>(foo) << '\n';
    std::cout << any_cast<char const*>(bar) << '\n';
}

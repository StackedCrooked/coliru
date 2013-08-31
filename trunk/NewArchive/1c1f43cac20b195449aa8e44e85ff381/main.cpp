#include <type_traits>
#include <utility>
#include <memory>
#include <typeinfo>
#include <string>
#include <vector>
#include <iostream>

class Any {
private:
    struct Base {
        virtual ~Base() {}
        virtual std::unique_ptr<Base> clone() const = 0;
    };

    std::unique_ptr<Base> obj;

    template<typename T>
    struct Derived : Base {
        template<typename U>
        Derived(U&& v): value(std::forward<U>(v)) {}
        T value;

        std::unique_ptr<Base> clone() const {
            return std::unique_ptr<Base>(new Derived<T>(value));
        }
    };

    std::unique_ptr<Base> clone() const {
        if(obj)
            return obj->clone();
        else
            return nullptr;
    }
public:
    template<typename T>
    using Decay = typename std::decay<T>::type;

    template<typename U>
    Any(U&& v): obj(new Derived<Decay<U>>(std::forward<U>(v))) {}
    Any(Any& that): obj(that.clone()) {}
    Any(Any&& that): obj(std::move(that.obj)) {}
    Any(const Any& that): obj(that.clone()) {}
    Any(const Any&& that): obj(that.clone()) {}
    Any() {}

    bool isNull() const {
        return !bool(obj);
    }
    bool notNull() const {
        return bool(obj);
    }

    template<typename U>
    bool is() const {
        auto derived = dynamic_cast<Derived<Decay<U>>*>(obj.get());
        return derived;
    }

    template<typename U>
    Decay<U>& as() {
        auto derived = dynamic_cast<Derived<Decay<U>>*>(obj.get());

        if(!derived)
            throw std::bad_cast();

        return derived->value;
    }

    template<typename U>
    const Decay<U>& as() const {
        auto derived = dynamic_cast<Derived<Decay<U>>*>(obj.get());

        if(!derived)
            throw std::bad_cast();

        return derived->value;
    }

    Any& operator=(const Any& other) {
        if(obj == other.obj)
            return *this;

        obj = other.clone();

        return *this;
    }

    Any& operator=(Any&& other) {
        if(obj == other.obj)
            return *this;

        swap(obj,other.obj);
        return *this;
    }

    template<typename U>
    operator U() const {
        return as<Decay<U>>();
    }
};

int main() {
    Any a;
    std::string str;
    a = str;
    if(a.is<std::string>())
        std::cout << "Whoa a string!\n";
    
    a = 1.2345;
    if(a.is<double>())
        std::cout << "Whoa a double?!?\n";
    
    a = 'a';
    if(a.is<char>())
        std::cout << "And now you're a character..\n";
}
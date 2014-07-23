#include <memory>
#include <string>
#include <iostream>

struct base {
    virtual ~base() = default;
    base() = default;

    virtual void modify(const std::string&) = 0;
};

template<typename T>
using is_pointer_no_ref = std::is_pointer<typename std::remove_reference<T>::type>;

template<typename T>
struct parser_type {
private:
    using no_ptr = typename std::remove_pointer<T>::type;
public:
    using type = typename std::conditional<is_pointer_no_ref<T>::value,
                                           std::function<no_ptr(const std::string&)>,
                                           std::function<T(const std::string&)>>::type;
};

template<typename T, typename U, typename std::enable_if<!is_pointer_no_ref<T>::value, int>::type = 0>
inline auto store_to(T&& t, U&& u) -> decltype(std::forward<T>(t) = std::forward<U>(u)) {
    return std::forward<T>(t) = std::forward<U>(u);
}

template<typename T, typename U, typename std::enable_if<is_pointer_no_ref<T>::value, int>::type = 0>
inline auto store_to(T&& t, U&& u) -> decltype(*std::forward<T>(t) = std::forward<U>(u)) {
    return *std::forward<T>(t) = std::forward<U>(u);
}

template<typename T, typename std::enable_if<is_pointer_no_ref<T>::value, int>::type = 0>
inline const T& dereference(const T& ptr) noexcept {
    return *ptr;
}

template<typename T, typename std::enable_if<!is_pointer_no_ref<T>::value, int>::type = 0>
inline const T& dereference(const T& val) noexcept {
    return val;
}

template<typename T>
struct derived : public base {
private:
    T value;
    typename parser_type<T>::type parser_;
public:
    derived() = default;
    derived(T val): value(std::move(val)) {}

    void modify(const std::string& stuff) override {
        auto&& result = parser_(stuff);
        store_to(value, result);
    }

    template<typename Action>
    derived& action(Action ac) {
        parser_ = ac;
        return *this;
    }

    const typename std::remove_pointer<T>::type& get() const noexcept {
        return dereference(value);
    }
};

template<typename T>
struct store {
    T operator()(const std::string&) const {
        return T();
    }
};

template<>
struct store<bool> {
    bool operator()(const std::string& stuff) const {
        return stuff == "1" || stuff == "true";
    }
};

template<typename T>
inline const T& get(const std::unique_ptr<base>& val) {
    auto ptr = dynamic_cast<derived<T>*>(val.get());
    if(ptr == nullptr) {
        throw std::runtime_error("invalid cast to derived");
    }

    return ptr->get();
}

template<typename T>
inline std::unique_ptr<base> value() {
    std::unique_ptr<derived<T>> stuff(new derived<T>());
    stuff->action(store<T>{});
    return std::unique_ptr<base>{std::move(stuff)};
}

template<typename T>
inline std::unique_ptr<base> bind_to(T& val) {
    std::unique_ptr<derived<T*>> stuff(new derived<T*>(&val));
    stuff->action(store<T>{});
    return std::unique_ptr<base>{std::move(stuff)};
}

int main() {
    auto&& ptr = value<bool>();
    ptr->modify("true");
    std::cout << get<bool>(ptr) << '\n';

    bool stuff;
    auto&& ptr2 = bind_to(stuff);
    ptr2->modify("true");
    std::cout << stuff;
}


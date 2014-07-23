#include <memory>
#include <string>

struct base {
    virtual ~base() = default;
    base() = default;

    virtual void modify(const std::string&) = 0;
};

template<typename T>
struct parser_type {
private:
    using no_ptr = typename std::remove_pointer<T>::type;
public:
    using type = typename std::conditional<std::is_pointer<T>::value,
                                           std::function<no_ptr(const std::string&)>,
                                           std::function<T(const std::string&)>>::type;
};

template<typename T, typename U, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
inline auto store_to(T&& t, U&& u) -> decltype(std::forward<T>(t) = std::forward<U>(u)) {
    return std::forward<T>(t) = std::forward<U>(u);
}

template<typename T, typename U, typename std::enable_if<std::is_pointer<T>::value, int>::type = 0>
inline auto store_to(T&& t, U&& u) -> decltype(*std::forward<T>(t) = std::forward<U>(u)) {
    return *std::forward<T>(t) = std::forward<U>(u);
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
    // what to do
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
}


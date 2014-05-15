#include <iostream>
#include <tuple>

//---------------------------------------------------
template<class...Ts>
class container
{
    using ts_type = std::tuple<Ts...>;

public:
    container() = default;

    container(Ts... ts) : ts_{std::move(ts)...} {}

    // get #1: member template
    template<std::size_t index>
    auto 
    get() const -> decltype(std::get<index>(std::declval<const ts_type>())) {
        return std::get<index>(ts_);
    }

    // get #2: friend function
    template<std::size_t index>
    friend typename std::tuple_element<index,ts_type>::type
    get(const container& c) {
        return std::get<index>(c.ts_);
    }

    // *********
    template<std::size_t index, class... Us>
    friend auto 
    get(const container<Us...>& c) -> decltype(std::get<index>(c.ts_));
    // *********

private:
    ts_type ts_;
};

// *********
template<std::size_t index, class... Us>
auto get(const container<Us...>& c) -> decltype(std::get<index>(c.ts_)) {
    return std::get<index>(c.ts_);
}
// *********

//---------------------------------------------------
template<class T>
void foo(const T& t) {
    // error: expected primary-expression before ')' token
    std::cout << t.template get<0>() << std::endl;

    // error: 'get' was not declared in this scope
    std::cout << get<0>(t) << std::endl;
}

//---------------------------------------------------
int main() {   
    // this compiles and runs just fine ... as expected
    auto c = container<int,double>{1, 2.5};

    std::cout << c.get<0>() << std::endl;
    std::cout << c.get<1>() << std::endl;

    std::cout << get<0>(c) << std::endl;
    std::cout << get<1>(c) << std::endl;
}
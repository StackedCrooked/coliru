#include <iostream>
#include <boost/optional.hpp>
#include <type_traits>

template<class T> using Unref = typename std::remove_reference<T>::type;

auto enumFrom = [](int start){
    return [=]() mutable -> boost::optional<int> {
        return start++;
    };
};

auto enumFromTo = [](int start){ return [=](int end) {
    return [=]() mutable -> boost::optional<int> {
        if (start <= end)
            return start++;
        return boost::none;
    };
};};

auto map = [](auto f){ return [=](auto xs){
    return [=]() mutable -> boost::optional<decltype(f(*xs()))>{
        if (auto x = xs())
            return f(*x);
        return boost::none;
    };
};};

auto print = [](auto xs){
    while(auto x = xs())
        std::cout << *x << ' ';
};

auto concat = [](auto xxs){
    using result = boost::optional<Unref<decltype(*(*xxs())())>>;
    decltype(xxs()) cache;
    return [=]() mutable -> result {
        while (cache || (cache = boost::in_place(*xxs())))
        {
            if (auto x = (*cache)())
                return *x;
            if (auto xs = xxs())
                cache = boost::in_place(*xs);
            else
                break;
        }
        return boost::none;
    };
};

auto concatMap = [](auto f){ return [=](auto xs){
    return concat(map(f)(xs));
};};

auto flip = [](auto f){
    return [=](auto a){ return [=](auto b){
        return f(b)(a);
    };};
};

auto take = [](

int main(){
    auto zs = enumFromTo(1)(10);
    auto f = [](int z){ return concatMap(flip(enumFromTo)(z))(enumFromTo(1)(z)); };
    auto xs = concatMap(enumFromTo(1))(zs);
    auto ys = concatMap(f)(zs);
    std::cout << '\n';
    print(ys);
}
#include <iostream>
#include <boost/optional.hpp>
#include <type_traits>
#include <tuple>

template<class T> using Unref = typename std::remove_reference<T>::type;

struct nil_t{
    boost::optional<nil_t> operator()() const { return boost::none; }
};

static const auto nil = nil_t{};

template<class T>
auto nil_of(){ return []{ return boost::optional<T>{}; }; }

static constexpr struct Unit{} unit{};

auto enumFrom = [](auto start){
    return [=]() mutable -> boost::optional<decltype(start)> {
        return start++;
    };
};

auto enumFromTo = [](auto start){ return [=](auto end) {
    return [=]() mutable -> boost::optional<decltype(start)> {
        if (start <= end)
            return start++;
        return boost::none;
    };
};};

auto map = [](auto f){ return [=](auto xs){
    return [=]() mutable -> boost::optional<decltype(f(*xs()))>{
        if (auto&& x = xs())
            return f(*x);
        return boost::none;
    };
};};

auto concat = [](auto xxs){
    using result = boost::optional<Unref<decltype(*(*xxs())())>>;
    using cache_t = decltype(xxs());
    auto updateCache = [](auto& c, auto& xxs) -> cache_t& {
        if (auto&& v = xxs())
            c = boost::in_place(*v);
        else
            c = boost::none;
        return c;
    };
    cache_t cache;
    
    return [=]() mutable -> result {
        while (cache || updateCache(cache, xxs))
        {
            if (auto&& x = (*cache)())
                return *x;
            else
                cache = boost::none;
        }
        return boost::none;
    };
};

auto concatMap = [](auto f){ return [=](auto xs){
    return concat(map(f)(xs));
};};

auto guard = [](bool b){
    auto v = boost::make_optional(b, unit);
    return [=]() mutable {
        auto r = v;
        v = boost::none;
        return r;
    };
};

auto singleton = [](auto e){
    auto v = boost::make_optional(e);
    return [=]() mutable {
        auto r = v;
        v = boost::none;
        return r;
    };
};

auto flip = [](auto f){
    return [=](auto a){ return [=](auto b){
        return f(b)(a);
    };};
};

auto concatMap_ = flip(concatMap);

int main(){
    auto xs = concatMap_(enumFromTo(1)(100))([](int z){
        return concatMap_(enumFromTo(1)(z))([=](int x){
            return concatMap_(enumFromTo(x)(z))([=](int y){
                return concatMap_(guard(x*x + y*y == z*z))([=](Unit){
                    return singleton(std::make_tuple(x, y, z));
                });
            });
        });
    });
    while (auto v = xs())
        std::cout << '(' << std::get<0>(*v) << ',' << std::get<1>(*v) << ',' << std::get<2>(*v) << ")\n";
}
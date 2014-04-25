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

auto null = [](auto xs) -> bool{
    return !xs();
};

auto cons = [](auto x){ return [=](auto xs){
    return [=, v = boost::make_optional(x)]() mutable {
        auto r = v ? v : xs();
        v = boost::none;
        return r;
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
    
    return [=, cache = cache_t{}]() mutable -> result {
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

auto foldl = [](auto f){ return [=](auto init){ return [=](auto xs){
    auto ret = boost::make_optional(init);
    while (auto v = xs())
    {
        ret = boost::in_place(f(*ret)(*v));
    }
    return *ret;
};};};

auto guard = [](bool b){
    return [v = boost::make_optional(b, unit)]() mutable {
        auto r = v;
        v = boost::none;
        return r;
    };
};

auto filter = [](auto pred){ return [=](auto xs){
    return [=]() mutable -> decltype(xs()){
        while (auto v = xs())
            if (pred(*v))
                return v;
        return boost::none;
    };
};};

auto take = [](int count){ return [=](auto xs){
    return [=]() mutable -> decltype(xs()){
        if (count-- > 0)
            return xs();
        count = 0;
        return boost::none;
    };
};};

auto drop = [](int count){ return [=](auto xs){
    return [=]() mutable {
        while (count-- > 0)
            (void)xs();
        count = 0;
        return xs();
    };
};};

auto takeWhile = [](auto pred){ return [=](auto xs){
    return [=, p = boost::make_optional(pred)]() mutable -> decltype(xs()){
        if (p)
        {
            decltype(xs()) v;
            if (p && (v = xs()) && (*p)(*v))
                return v;
            p = boost::none;
        }
        return boost::none;
    };
};};

auto dropWhile = [](auto pred){ return [=](auto xs){
    return [=, p = boost::make_optional(pred)]() mutable {
        if (p)
        {
            decltype(xs()) v;
            while ((v = xs()) && (*p)(*v))
                ;
            p = boost::none;
            return v;
        }
        return xs();
    };
};};

auto span = [](auto pred){ return [=](auto xs){
    return std::make_tuple(takeWhile(pred)(xs), dropWhile(pred)(xs));
};};

auto singleton = [](auto e){
    return [v = boost::make_optional(e)]() mutable {
        auto r = v;
        v = boost::none;
        return r;
    };
};

auto toStream = [](auto xs){
    using std::begin;
    using std::end;
    return [curr = begin(xs), r = std::move(xs)]() mutable -> boost::optional<decltype(*begin(xs))>{
        if (curr != end(r))
            return *curr++;
        return boost::none;
    };
};

auto flip = [](auto f){
    return [=](auto a){ return [=](auto b){
        return f(b)(a);
    };};
};

auto concatMap_ = flip(concatMap);

#include <vector>

int main(){
    std::vector<int> v{1,2,3,4,5};
    auto l = toStream(v);
    while(auto v = l())
        std::cout << *v << ' ';
}
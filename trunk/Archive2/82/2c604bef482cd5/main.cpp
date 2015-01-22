#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

//template <typename T1,typename T2> class Functor {
//public:
//    Functor( T1 T2::* t):memPointer(t) {}
//    bool operator() (const T2 & obj1, const T2 & obj) {
//        return obj1.*memPointer < (obj.*memPointer);
//    }
//    
//    T1 T2::* memPointer;
//};

// Functor<T1, T2> == std::function<bool(T2 const&, T2 const&)>

template <typename V, typename T>
static inline auto make_member_cmp(V T::* t) -> std::function<bool(T const&, T const&)> {
    return [t](T const &lhs, T const &rhs) -> bool {
        return lhs.*(t) < rhs.*(t);
    };
}

struct ABC{
    double x;
    double y;
};

int main() {
    std::vector<ABC> vec { {9, 89}, {10, 10}, {5, 100} };

    auto bb = make_member_cmp(&ABC::x); //make_functor(&ABC::x);
    std::sort(vec.begin(),  vec.end(),  bb);
    std::for_each(std::begin(vec), std::end(vec),
        [](ABC const &v) { std::cout << v.x << std::endl; }
    );
    
    std::cout << "——————–" << std::endl;
    
    bb = make_member_cmp(&ABC::y);
    std::sort(vec.begin(),  vec.end(),  bb);
    std::for_each(std::begin(vec), std::end(vec),
        [](ABC const &v) { std::cout << v.y << std::endl; }
    );
    
    return 0;
}

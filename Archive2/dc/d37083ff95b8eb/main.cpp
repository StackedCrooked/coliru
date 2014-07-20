#include <tuple>
#include <algorithm>
#include <iterator>
#include <iostream>
using std::begin;
using std::end;

template<class T, typename... types>
struct member_comparer {
    member_comparer(types T::*...  args) : ptrs(args...) { }
    
    
    bool operator()(const T& t1, const T& t2){
        return do_compare(t1, t2, std::make_index_sequence<sizeof...(types)>());
    }
    
    private:
    template<size_t... indices>
    bool do_compare(const T& t1, const T& t2, std::index_sequence<indices...> ){
        return std::tie(t1.*std::get<indices>(ptrs)...) < std::tie(t2.*std::get<indices>(ptrs)...);
    }
    
    std::tuple<types T::* ...> ptrs;
};

template<class T, typename... types>
member_comparer<T, types...> make_member_comparer(types T::*...  args) { return member_comparer<T, types...>(args...); }


struct A{
    int x;
    double y;
    float z;
};

int main() { 
    A a[3] = { { 1, 4, 5}, { 2, 3, 4}, {4, 4, 9}};
    auto comp_x_only = make_member_comparer(&A::x);
    auto comp_y_then_x = make_member_comparer(&A::y, &A::x);
    
    std::sort(begin(a), end(a), comp_x_only);
    for(const auto & e : a){
        std::cout << e.x << ' ' << e.y << ' ' << e.z << std::endl;
    }
    
    std::sort(begin(a), end(a), comp_y_then_x);
    for(const auto & e : a){
        std::cout << e.x << ' ' << e.y << ' ' << e.z << std::endl;
    }
    
}
#include <tuple>
#include <functional>

template<class T>
struct binder {
    T v;    
    binder(T v_) :v(std::forward<T>(v_)) {}    
    const T& get() const {return v;}  
};
    
template<class L,class R> 
std::tuple<L,R> operator,(const binder<L>& lhs, const binder<R>& rhs) 
{return std::tuple<L,R>(lhs.get(),rhs.get());}

template<class P0, class P1, class R> 
std::tuple<P0,P1,R> operator,(const std::tuple<P0,P1>& lhs, const binder<R>& rhs) 
{return std::tuple<P0,P1,R>(std::get<0>(lhs),std::get<1>(lhs),rhs.get());}  

template<class func_type, class P0, class P1, class P2> 
auto operator->*(const std::tuple<P0, P1, P2>& t, func_type&& func) 
->decltype(func(std::get<0>(t),std::get<1>(t),std::get<2>(t)))
{return func(std::get<0>(t),std::get<1>(t),std::get<2>(t));}






#include <iostream>

void thing(binder<int> width, binder<int> height, binder<int> depth) {
    int volume = (width,height,depth) ->* [] (int w, int h, int d) { return w * h * d; };
    std::cout << volume;
}

int main()
{
    thing(3, 4, 5);
}
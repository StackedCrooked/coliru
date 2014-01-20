#include <iostream>
#include <utility>
#include <functional>
#include <tuple>

template<int...> struct seq{ using type = seq; };
template<int I, int... Is> struct gen_seq : gen_seq<I-1, I-1, Is...>{};
template<int... Is> struct gen_seq<0, Is...> : seq<Is...>{};

template<class T>
using Decay = typename std::decay<T>::type;

template<class T>
struct unref{ using type = T; };
template<class T>
struct unref<std::reference_wrapper<T>>{ using type = T&; };

template<class T>
using DecayUnref = typename unref<Decay<T>>::type;

template<class F, class... B>
struct prebind_t{
    F _f;
    std::tuple<B...> _bound;
    
    using my_seq = typename gen_seq<sizeof...(B)>::type;
    template<class... Args>
    using result = typename std::result_of<F(B&..., Args...)>::type;
    
    template<class... Args>
    result<Args...> operator()(Args&&... args) const
    {
        call(my_seq{}, std::forward<Args>(args)...);
    }
    
    template<int... Is, class... Args>
    result<Args...> call(seq<Is...>, Args&&... args) const
    {
        return _f(std::get<Is>(_bound)..., std::forward<Args>(args)...);
    }
};

template<class F, class... B>
prebind_t<Decay<F>, DecayUnref<B>...> prebind(F&& f, B&&... b){
    return {std::forward<F>(f), std::forward_as_tuple(std::forward<B>(b)...)};
}

void f(int, int& i, int){ i = 100; }

int main(){
    int i = 1337;
    prebind(f, 42, std::ref(i))(0);
    std::cout << i << "\n";
}
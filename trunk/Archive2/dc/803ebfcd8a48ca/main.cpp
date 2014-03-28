#include <iostream>
#include <future>
#include <thread>
#include <string>

void func_string( std::string const&x) {
    std::cout << x << " ";
}

void func_int(int x) {
    std::cout << x << " ";
}

template <typename T_>
using decay_t = typename std::decay<T_>::type;
template< class T >
using result_of_t = typename std::result_of<T>::type;

template <typename F, typename A>
std::future<result_of_t<decay_t<F>(decay_t<A>)>> spawn_task(F &&f, A &&a) {
    using result_t = result_of_t<decay_t<F>(decay_t<A>)>;
    std::packaged_task< result_t(decay_t<A>)> task(std::forward<F>(f));
    auto res = task.get_future();
    std::thread t(std::move(task), std::forward<A>(a));
    t.detach();
    return res;
}

int main() {
    std::string str = "abc";

    auto res1 = spawn_task(func_string, str);
    res1.get();
    std::cout << str << "\n";
    
    auto res2 = spawn_task( func_string, std::move(str) );
    res2.get();
    std::cout << str << "\n";
    
    auto res3 = spawn_task(func_int, 10);
    res3.get();
}
#include <iostream>
#include <future>
#include <thread>
#include <string>
int func_string(const std::string &x) 
{
    return 1;
}

int func_int(int x) 
{
    return 2;
}

template <typename F, typename A>
std::future<typename std::result_of<F(A)>::type> spawn_task(F &&f, A &&a) 
{
    typedef typename std::result_of<F(A)>::type result_type;
    std::packaged_task<result_type(A)> task(std::move(f));
    std::future<result_type> res(task.get_future());
    std::thread t(std::move(task), std::move(a));
    t.detach();
    return res;
}

int main()
{
    std::string str = "abc";

     auto res1 = spawn_task(func_string, str);
     res1.get();
    auto res2 = spawn_task(func_int, 10);
    res2.get();
}
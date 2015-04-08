#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <functional>


#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
#define BOOST_THREAD_PROVIDES_FUTURE_UNWRAP
#define BOOST_THREAD_PROVIDES_EXECUTORS

#include <boost/thread/future.hpp>
#include <boost/thread/executor.hpp>
#include <boost/thread/executors/basic_thread_pool.hpp>
#include <boost/thread/executors/serial_executor.hpp>
#include <boost/thread/executors/thread_executor.hpp>

using namespace boost;


//auto launch_policy = boost::launch::deferred;
//auto launch_policy = boost::launch::async;
auto launch_policy = boost::launch::executor;


void async_atoi2(boost::future<std::string> arg, boost::promise<int> p)
{
    std::cout <<"async_atoi: " << std::this_thread::get_id() << std::endl;
    p.set_value(std::stoi(arg.get()));
}


void async_itoa2(boost::future<int> arg, boost::promise<std::string> p)
{
    std::cout <<"async_itoa: " << std::this_thread::get_id() << std::endl;

    p.set_value(std::to_string(arg.get()));
}

template <typename F, typename T>
std::function<boost::future<T>(boost::future<F>)> wrap(std::function<void(boost::future<F>, boost::promise<T>)> f)
{    
    return [=](boost::future<F> arg) -> boost::future<T>
    {
        boost::promise<T> p;
        auto f = p.get_future();
        std::thread(std::bind(f, arg, std::move(p))).detach();
        return f;
    };
}



boost::future<int> async_atoi(boost::future<std::string> arg)
{
    std::cout <<"async_atoi: " << std::this_thread::get_id() << std::endl;
    boost::promise<int> p;
    p.set_value(std::stoi(arg.get()));
    return p.get_future();
}


boost::future<std::string> async_itoa(boost::future<int> arg)
{
    std::cout <<"async_itoa: " << std::this_thread::get_id() << std::endl;

    boost::promise<std::string> p;
    p.set_value(std::to_string(arg.get()));
    return p.get_future();
}

void test_future_executor()
{
    boost::basic_thread_pool ex(1);
    boost::promise<std::string> p;
    p.set_value("123");
    /*
    auto s_atoi = []() -> boost::future<int>
    {
        std::cout <<"s_atoi: " << std::this_thread::get_id() << std::endl;
        boost::promise<int> p;
        auto ret = p.get_future();
        p.set_value(std::stoi("123"));
        return ret;
    };
    */
    auto s_atoi2 = []() -> int
    {
        std::cout <<"s_atoi: " << std::this_thread::get_id() << std::endl;
        return std::stoi("123");
    };
    auto f2 = boost::async(ex, s_atoi2);//.get();
    /*
    auto f = async_atoi(p.get_future()).then(ex, async_itoa).get();

    auto f1 = f.then(ex, async_atoi).get();
    auto f2 = f1.then(ex,
                    [](future<int> f) {
                      std::cout << "main then: " << std::this_thread::get_id() << std::endl;
                      std::cout << f.get() << std::endl; // here .get() won't block
                        return std::string("sgfsdfs");
                    });   
 */
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //std::cout << "main again: " << f2.get() << std::endl;                   
}


void test_future()
{
    boost::promise<std::string> p;
    p.set_value("123");
    
    auto f = async_atoi(p.get_future()).then(launch_policy, async_itoa).get();
    auto f1 = f.then(launch_policy, async_atoi).get();
    auto f2 = f1.then(launch_policy,
                    [](future<int> f) {
                      std::cout << "main then: " << std::this_thread::get_id() << std::endl;
                      std::cout << f.get() << std::endl; // here .get() won't block
                        return std::string("sgfsdfs");
                    });   
 
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "main again: " << f2.get() << std::endl;                   
}

void test_future_cont()
{
    boost::promise<std::string> p;
    p.set_value("123");
    
    auto f = async_atoi(p.get_future()).then(launch_policy, async_itoa).get().then(
        launch_policy, async_atoi).get().then(
        launch_policy, [](future<int> f) {
                      std::cout << "main then: " << std::this_thread::get_id() << std::endl;
                      std::cout << f.get() << std::endl; // here .get() won't block
                        return std::string("sgfsdfs");
                    });    
 
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "main again: " << f.get() << std::endl;                   
}
/*
void test_future_executor()
{
    //boost::executor_adaptor<boost::serial_executor> ex();
    boost::basic_thread_pool ex(1);
    
    boost::promise<std::string> p;
    p.set_value("123");
    
    auto f = async_atoi(p.get_future()).then(ex, async_itoa).get().then(
        ex, async_atoi).get().then(
        ex, [](future<int> f) {
                      std::cout << "main then: " << std::this_thread::get_id() << std::endl;
                      std::cout << f.get() << std::endl; // here .get() won't block
                        return std::string("sgfsdfs");
                    });    
 
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "main again: " << f.get() << std::endl;                   
}
*/
int main() {
   std::cout << "main: " << std::this_thread::get_id() << std::endl;

    boost::promise<std::string> p;
    p.set_value("123");
    /*auto f = wrap<std::string, int>(async_atoi2)(p.get_future()).then(launch_policy,
        wrap<int, std::string>(async_itoa2)).then(launch_policy,
        wrap<std::string, int>(async_atoi2)).then(launch_policy,
        [](future<int> f) {
            std::cout << "main then: " << std::this_thread::get_id() << std::endl;
            std::cout << f.get() << std::endl; // here .get() won't block
             return std::string("sgfsdfs");
        });
        */
        /*
    auto f = async_atoi(p.get_future()).then(launch_policy,
                async_itoa).unwrap().then(launch_policy,
                async_atoi).unwrap().then(launch_policy,
                    [](future<int> f) {
                      std::cout << "main then: " << std::this_thread::get_id() << std::endl;
                      std::cout << f.get() << std::endl; // here .get() won't block
                        return std::string("sgfsdfs");
                    });
                    */
                    
                    /*

                    */

    test_future_executor();                 
                    
    std::cout << "main " << std::endl;
    return 0;
}

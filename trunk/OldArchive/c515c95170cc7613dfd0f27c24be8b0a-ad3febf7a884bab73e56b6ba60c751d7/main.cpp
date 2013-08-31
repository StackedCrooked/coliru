#include <iostream>
#include <future>


namespace nonstd {

template<typename T>
struct future;


// This async does not return a blocking future
template< class Function, class... Args>
nonstd::future<typename std::result_of<Function(Args...)>::type> async( Function&& f, Args&&... args );

template<typename T>
struct future : std::future<T> {
    using std::future<T>::future;
    
    // conversion constructor
    future(std::future<T>&& rhs) : std::future<T>(std::move(rhs)) {}
    
    template<typename F>
    auto then(F f) -> nonstd::future<decltype(f(std::declval<T>()))> {
        return nonstd::async([=] () {
            return f(std::future<T>::get());
        });
    }
};

template<typename T>
nonstd::future<T> make_nonstd(std::future<T> f)
{
    return nonstd::future<T>(std::move(f));
}

// This async does not return a blocking future
template< class Function, class... Args>
nonstd::future<typename std::result_of<Function(Args...)>::type> async( Function&& f, Args&&... args ) 
{
    typedef typename std::result_of<Function(Args...)>::type R;
    auto bound_task = std::bind(std::forward<Function>(f), std::forward<Args>(args)...);
    std::packaged_task<R()> task(std::move(bound_task));
    auto ret = make_nonstd(std::move(task.get_future()));
    std::thread t(std::move(task));
    t.detach();
    return ret;   
}


} // namespace nonstd


// http_get using a std::future
nonstd::future<std::string> http_get(const std::string& url)
{
    return nonstd::async([=]() -> std::string {
        return "<html>" + url + "</html>";
    });
}


template<typename Future, typename Callback>
nonstd::future<void> then(Future future, Callback callback)
{
    auto future_ptr = std::make_shared<Future>(std::move(future));
    return really_async(std::launch::async, [=]() {
        callback(future_ptr->get());
    });
}



int main()
{    
    // using std::future
    nonstd::future<std::string> page = http_get("google.com");
    page.then([=](const std::string& str) -> std::string {
        std::cout << "We got it: " << str << std::endl << std::endl << '\n';
        return str;
    }).then([=](const std::string & str) -> void {
        std::cout << "After party: " << str << "!!" << std::endl;
    }).wait();
}
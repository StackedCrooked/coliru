#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <queue>
#include <condition_variable>
#include <vector>

template<typename Data>
class concurrent_queue
{
private:
    std::queue<Data> the_queue;
    mutable std::mutex the_mutex;
    std::condition_variable the_condition_variable;
public:
    void push(Data const& data)
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        the_queue.push(data);
        lock.unlock();
        the_condition_variable.notify_one();
    }

    bool empty() const
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        return the_queue.empty();
    }

    bool try_pop(Data& popped_value)
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        if(the_queue.empty())
        {
            return false;
        }
        
        popped_value=the_queue.front();
        the_queue.pop();
        return true;
    }

    Data pop()
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        while(the_queue.empty())
        {
            the_condition_variable.wait(lock);
        }
        
        Data& popped_value=the_queue.front();
        the_queue.pop();
        return popped_value;
    }
};

template<typename Fut, typename F, typename T>
void set_value( std::promise<Fut>& p, F& f, T& t ) { p.set_value( f(t) ); }
template<typename F, typename T>
void set_value( std::promise<void>& p, F& f, T& t ) { f(t); p.set_value(); }

template<typename T>
class concurrent
{
    private:
        mutable T t;
        mutable concurrent_queue<std::function<void()>> q;
        bool done = false;
        std::thread thd;
    public:
        concurrent( T t_ ) : t{t_}, thd{[=]{ while(!done) q.pop()(); }} { }
        ~concurrent() { q.push([=]{ done=true; }); thd.join(); }
        template<typename F>
        auto operator()( F f ) const -> std::future<decltype(f(t))> { 
            auto p = std::make_shared<std::promise<decltype(f(t))>>();
            auto ret = p->get_future();
            q.push([=]{
                try { set_value( *p, f, t ); }
                catch(...) { p->set_exception(std::current_exception()); }
                });
            return ret;
        }
};
int main()
{
    concurrent_queue<int> data;
    auto handle1=std::async(std::launch::async,[&data](){
        int value=data.pop();
        std::cout<<"Popped:"<<value<<std::endl;
        });
    auto handle2=std::async(std::launch::async,[&data](){
        std::cout<<"Pushed"<<std::endl;
        data.push(12);
        });
    //using concurrent
    std::string my_string;
    concurrent<std::string> s(my_string);
    std::vector<std::future<void>> v;
    for(int i=0;i<10;i++)
    {
        std::cout<<"starting:"<<i<<std::endl;
        v.push_back(std::async(std::launch::async,[&,i](){
        auto f = s([i](std::string& s){ // thread safe transaction!
            s += std::to_string(i) + " " + std::to_string(43);
            return std::string("*** set : ") + s;
        });
        }));
    }
    for(size_t i=0;i<v.size();i++)
        v[i].wait();
    return 0;
}
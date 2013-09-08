#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/bind/protect.hpp>
#include <boost/bind/apply.hpp>
#include <iostream>

typedef boost::function<void(int)> SomeCallback;
typedef boost::function<void()>    Task;

void handler(int i){
    std::cout << "i=" << i <<std::endl;
}

void subscribe(SomeCallback cb)
{
    cb(100);  //just invoke the callback for simplicity
}

void postToTaskQueue(Task t)
{
    t();  // just invoke the task for simplicity
}

void helper(SomeCallback cb, int i)
{
    postToTaskQueue(boost::bind(cb, i));
}

void subscribe2(SomeCallback cb)
{
    using boost::bind;
    using boost::protect;
    using boost::apply;

    bind(cb, 41)(); // OK of course
    postToTaskQueue(bind(cb, 46)); // also find
    bind(postToTaskQueue, protect(bind(cb, 146)))(); // boost::protect to the rescue

    postToTaskQueue(bind(apply<void>(), cb, 47));
    bind(postToTaskQueue, protect(bind(apply<void>(), cb, 147)))();

    // but sadly, this appears to not work ...
    auto hmm = bind(postToTaskQueue, bind(apply<void>(), cb, _1));
    //hmm(997); // FAIL
}
int main()
{
    subscribe (boost::bind(handler, _1));
    subscribe2(boost::bind(handler, _1));
}

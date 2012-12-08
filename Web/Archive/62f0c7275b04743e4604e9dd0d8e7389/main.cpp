#include <future>
#include <iostream>


template<typename R>
std::future<R> schedule_function(R (&func)())
{
    std::shared_ptr< std::promise<R> > prom = std::make_shared<std::promise<R> >();
    auto l = [=]() {  prom.set_value(func()); };
    return prom->get_future();    
}

int main()
{
}
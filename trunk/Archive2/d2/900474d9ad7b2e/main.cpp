
#include <future>

int main()
{
    // equivalent of happens in consumer thread, when starting up the work item
    // the promise itself is stored in the work item
    std::shared_ptr<std::promise<int>> p(std::make_shared<std::promise<int>>());
    
    // worker thread races with consumer, setting the value...
    // happens in worker thread
    p->set_value(1);
    // work item done, destructed by worker thread (promise gets destructed)
    p.reset();
    
    // happens in consumer thread (that consumes the future result)
    // after it returns from enqueueing the item
    // the workitem got done so fast that the whole promise is gone,
    // it destructed with the work item
    std::future<int> f = p->get_future();
}

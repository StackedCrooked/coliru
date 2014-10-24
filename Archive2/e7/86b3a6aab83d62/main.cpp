#include <iostream>
#include <functional>
#include <future>
#include <thread>
#include <utility>
#include <vector>


// I'd like to put a packaged_task with an arbitrary function type and arbitrary
// arguments (saved perhaps as unique_ptr) in this so I can enqueue it.
// I've been doing it with void* and forcing the API consumer to remember
// to cast and delete them :(
class TaskWrapper
{
    /* T? */ void* the_arg { nullptr };
    /* T? */ void* the_task { nullptr };
	/* T? */ void* the_future { nullptr };
	
public:
	TaskWrapper(/* ??? */) {}
};


// This is the client-facing method
template<typename F, typename... Args>
auto make_task(F&& f, Args&& ... args) 
  -> std::future<typename std::result_of<F(Args...)>::type>
{
	using return_type = typename std::result_of<F(Args...)>::type;
    
    auto task = std::make_shared<std::packaged_task<return_type()>>(
      std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );
    
    // This works in my threadpool as a quick test
    std::vector<std::function<void()>> tasks;
    tasks.emplace([task]() { (*task)(); });
    
    return task->get_future();
}

int the_target(int i) 
{
	return i+5;
}

int main() {

    auto fut = make_task(the_target, 5);
    
	
	// But I'd like to wrap the task and enqueue the wrapper instead
	TaskWrapper tw(/* ??? */);

    // But I can't work out the types unless I just store the lambda
    
    // Is that idiomatic?
	
	return 0;
}
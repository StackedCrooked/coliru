
#include <future>

typedef std::function<void()> F;

F faux_queue_slot;

void runLater(F f)
{
    faux_queue_slot = std::move(f);
}

struct W
{
    std::promise<int> p;
    
    explicit W(std::future<int>& future) { future = p.get_future(); }
    W(W &&r) : p(std::move(r.p)) {}
    W& operator=(W r) { p = std::move(r.p); return *this; }
    W(W const&r) = delete;
    
    void operator()()
    {
        // sometime in another thread
        p.set_value(1);
    }
};

int main()
{
    std::future<int> fut;
    runLater(W(fut));
}

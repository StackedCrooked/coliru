
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
    
    void operator()()
    {
        p.set_value(1);
    }
};

int main()
{
    runLater(W());
}

#include <thread>
#include <iostream>
#include <stack>

struct Context
{
    void *x;
    Context() { std::cout << "Context constructed" << std::endl; }
    ~Context() { std::cout << "Context destructed" << std::endl; }
};

class ContextGuard
{
    typedef std::stack<Context> ContextStack;

    static __thread ContextStack *contextStack;

    static ContextStack &Stack()
    {
        if (contextStack)
            return *contextStack;
        contextStack = new ContextStack;
        return *contextStack;
    }
    
    static void EnterContext()
    {
        Stack().push(Context());
    }
    
    static void ExitContext()
    {
        auto &s = Stack();
        s.pop();
        if (s.empty())
        {
            delete contextStack;
            contextStack = 0;
            std::cout << "Deleted empty stack" << std::endl;
        }
    }
    
    static Context &CurrentContext()
    {
        return Stack().top();
    }
    
public:
    ContextGuard() { EnterContext(); }
    ~ContextGuard() { ExitContext(); }
    Context *operator->() { return &CurrentContext(); }
};

__thread ContextGuard::ContextStack *ContextGuard::contextStack;

void TestTLStk(int depth = 0)
{
    if (depth == 3)
        return;
        
    ContextGuard ctx;
    TestTLStk(depth+1);
}

int main()
{
    for (auto i = 0; i < 100; ++i)
    {
        auto t0 = std::thread(TestTLStk, 0);
        auto t1 = std::thread(TestTLStk, 0);
        t0.join();
        t1.join();
        std::cout << "--------------------------------" << std::endl;
    }
    return 0;
}

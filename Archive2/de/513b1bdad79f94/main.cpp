#include <utility>

struct A
{
    A& operator()() & { return *this; }
    A& operator()() && = delete;
};

template <typename FUNC>
A& executeForwarding(FUNC&& f)
{
    return std::forward<FUNC>(f)();
}

template <typename FUNC>
A& executeNotForwarding(FUNC&& f)
{
    return f();
}

int main()
{
    // A& a1 = executeForwarding(A{}); // ok, this won't compile: "use of deleted function 'A& A::operator()() &&'"
    
    A& a2 = executeNotForwarding(A{}); // oops!, temporary bound to modifiable reference!
}

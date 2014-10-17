#include <utility>

struct A
{
    A& operator()() & { return *this; }
    A& operator()() && = delete;
};

struct B
{
    B& operator()() { return *this; }
};

template <typename FUNC>
A& executeA(FUNC&& f)
{
    return std::forward<FUNC>(f)();
}

template <typename FUNC>
B& executeB(FUNC&& f)
{
    return std::forward<FUNC>(f)();
}

int main()
{
    // A& a = executeA(A{}()); // ok, this won't compile: "use of deleted function 'A& A::operator()() &&'"
    
    B& b = executeB(B{}()); // oops!, temporary bound to modifiable reference!
}

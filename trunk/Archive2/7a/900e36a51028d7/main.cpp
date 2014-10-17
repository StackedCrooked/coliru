
struct A
{
    A& operator()() & { return *this; }
    A& operator()() && = delete;
};

struct B
{
    B& operator()() { return *this; }
};

int main()
{
    // A& a = A{}(); // ok, this won't compile: "use of deleted function 'A& A::operator()() &&'"
    
    B& b = B{}(); // oops!, temporary bound to modifiable reference!
}

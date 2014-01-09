template <typename... T> struct A { 
    A()          = default;
    virtual ~A() = default; // silence -Weffc++ warning
    
    // this is the cinch:
    template <typename... U> A(A<U...> const&) {}
};

template <typename... T>
struct B : A<T...>
{
    int _state;

    // follow the book
    B(int truth = 1) : _state(truth) { }
    B(B const&)            = default;
    B(B&&)                 = default;
    B& operator=(B const&) = default;
    B& operator=(B&&)      = default;
    
    // and just inherit ctors:
    using A<T...>::A;
};

int main()
{
    A<int> a;
    B<int> b = a;
}

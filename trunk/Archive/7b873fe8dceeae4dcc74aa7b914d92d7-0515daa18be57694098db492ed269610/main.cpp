void g(int*) {}

void f()
{
    g(sizeof(int) - sizeof(int)); // ok, evaluates to 0
}

template<typename T>
struct A
{
    void f()
    {
        g(sizeof(T) - sizeof(T)); // error: no matching function
    }
};

int main(){}
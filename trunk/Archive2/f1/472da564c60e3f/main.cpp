#include <cstdio>

template <typename T>
class C
{
public:
    C(T* buffer) : buffer(buffer) {}

    const T* get() const { return buffer; }
    T* get() { return buffer; }

    void increment() const { counter++; }

private:
    T* buffer;
    mutable int counter;
};

void function(int* n1, const int* n2)
{
    C<int>             a(n1);
    C<const int>       b(n2);
    const C<int>       c(n1);
    const C<const int> d(n2);

    // Reading the value is always allowed
    std::printf("%d %d %d %d",
       a.get()[0], b.get()[0],
       c.get()[0], d.get()[0]
    );

    // Incrementing the counter is always allowed
    a.increment();
    b.increment();
    c.increment();
    d.increment();

    // Can set non-const pointer
    a.get()[0] = 5;

    // Cannot set const pointer, or const/non-const pointer behind const object
    //b.get()[0] = 5;
    //c.get()[0] = 5;
    //d.get()[0] = 5;
}


int main()
{
    int x[] = {1,2,3,4,5};
    const int y[] = {1,2,3,4,5};
    
    function(x, y);
}
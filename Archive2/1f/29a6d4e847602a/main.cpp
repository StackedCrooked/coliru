template<typename T>
struct A { 
    A(T) {}
};

struct B: A<int>
{
    B()
    : A(17)
    {}
};


template<typename T>
struct C: A<T>
{
    C()
    : A(17)
    {}
};


int main() {
    B b;
    C<int> c;
    return 0;
}
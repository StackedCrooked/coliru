template <typename T>
struct type{};

struct A
{
    template<typename T>
    void operator()(type<T>) { }
};

int main()
{
    A a;
    
    a(type<int>());
}

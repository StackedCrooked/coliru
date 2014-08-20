template <typename T>
struct type_{};

template <typename T>
constexpr type_<T> type{};

struct A
{
    template<typename T>
    void operator()(type_<T>) { }
};

int main()
{
    A a;
    
    a(type<int>);
}

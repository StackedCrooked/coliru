template<typename... T>
struct Functor
{
    template <T...>
    using Inner = void;
};

using type = Functor<>::Inner<>;
    
int main() {}
template<typename T> 
constexpr auto X      = 1;

template<>           
constexpr auto X<int> = 2;

template<>
constexpr auto X<int*> = 0x2;

template<typename T> 
constexpr auto X<T*>  = 3 + X<T>;

int main()
{
        static_assert(X<int*> == 0x5, "");
}
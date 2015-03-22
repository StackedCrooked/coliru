void f();

template<typename T>
struct print_type;

int main()
{
    print_type<
      decltype(f)
    >{};
}
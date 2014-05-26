struct X{ void f(); };
struct Y : X{};

template<class> struct dump;

int main()
{
    dump<decltype(&Y::f)>{}
}

struct peek {};

template<typename Val>
void operator->*(peek, Val const&)
{}

template<typename...>
int foo() { return 0; }

int main()
{
    peek p;
    p->*foo<int, void, double>();
}
template<class T>
void foo() {}

template<int T>
void foo() {}

int main()
{
    foo<double>();
    foo<1>();
}
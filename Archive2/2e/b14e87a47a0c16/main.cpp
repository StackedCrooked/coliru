template<typename T>
void foo() {}

template<int i>
void foo() {}

int main()
{
    foo<42>();
}
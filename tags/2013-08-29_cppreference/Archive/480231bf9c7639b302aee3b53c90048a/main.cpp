template<int>
struct wat;

template<int I, typename T>
typename wat<I>::type foo(T);

int main()
{
    foo<0>(42);
}
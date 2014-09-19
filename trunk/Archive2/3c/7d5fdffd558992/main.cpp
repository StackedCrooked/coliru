
template<int I> void f(int, long, double*){}

int main()
{
    bool b = f<4>;
}

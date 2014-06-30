template <typename ...T>
void method(int param) throw (T...) {}

int main()
{
    method<int, bool>(42);
}
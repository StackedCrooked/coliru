template <typename T>
T foo()
{
    return T();
}

int main()
{
    foo<void>();
}

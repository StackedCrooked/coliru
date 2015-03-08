template <typename T>
void foo()
{
    return T();
}

int main()
{
    foo<void>();
}

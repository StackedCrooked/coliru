struct MyClass{};

void doBar(const MyClass * const * someFoo) {}

int main()
{
    MyClass i,j,k;
    MyClass * const foo[] = {&i, &j, &k};
    doBar(foo);
}
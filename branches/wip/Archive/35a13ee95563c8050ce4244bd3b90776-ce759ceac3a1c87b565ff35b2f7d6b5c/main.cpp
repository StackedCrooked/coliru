// Question: Why can't I use brace enclused initializer list to call copy constructor?

struct Foo
{
    int a;
};

int main()
{
    Foo f1{42};
    Foo f2{f1};
}

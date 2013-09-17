struct A
{
    explicit A(){}
};

void f(A){}

int main()
{
    f({});
}
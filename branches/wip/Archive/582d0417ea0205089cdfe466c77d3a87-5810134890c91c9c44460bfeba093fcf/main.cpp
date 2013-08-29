struct foo {
    void operator+() {}
};

struct bar: foo {};

int main()
{
    bar b; +b;
}
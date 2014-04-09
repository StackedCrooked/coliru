#define throw(...) __attribute__((deprecated)) throw(__VA_ARGS__)

void f()
{
    throw 42;
}

void g() throw(int)
{
    throw 42;
}

int main()
{}

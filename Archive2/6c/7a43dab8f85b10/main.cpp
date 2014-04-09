#define throw(...) __attribute__((deprecated)) throw(__VA_ARGS__)

void f() throw(int)
{
    throw 42;
}

int main()
{}

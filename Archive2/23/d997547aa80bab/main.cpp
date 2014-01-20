template <typename T>
struct Base
{
};

struct Derived : Base<int>
{
    Base* ptr;
};

int main()
{
    Derived d;
}

/**
 * in GCC 4.4.1:
 * 
 * error: ISO C++ forbids declaration of "Base" with no type
 */
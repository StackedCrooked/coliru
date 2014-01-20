#include <cstdio>

class B
{
public:
    B() { printf("B() : %p\n", this); }
    B(const B& b) { printf("B(const B& b) : %p %p\n", this, &b);}
    B& operator=(const B& b) { printf("B& operator=(const B& b) : %p %p\n", this, &b); return *this;}
};

class A
{
public:
    operator B() const
    {
        return b; 
    }

    B b;
};

int main() {
    A a;
    static_cast<B>(a);
}
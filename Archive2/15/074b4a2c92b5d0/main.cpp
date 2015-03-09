#include <cstddef>

template <class T>
class foo
{
    T* ptr;
    size_t size;
public:
    foo() : ptr(nullptr) {};
    foo(T* ptr, size_t size) : ptr(ptr), size(size) {};
    template <class U> operator U*()
    {
        return (U*) ptr;
    };
    T& operator[](unsigned int i)
    {
        return i < size ? ptr[i] : ptr[size - 1];
    }
    T& operator*()
    {
        return *ptr;
    }
};


int main()
{
    foo<char> Foo("ABC", 4);

    auto A = Foo[0];    // (char) 0x41 'A'
    int B = *Foo;       // 0x00000041
    int C = Foo[0];     // 0x00000041
    int* D = Foo;       // &"ABC"
    char* E = &Foo[1];  // &"BC"
    char* F = &Foo[4];  // &""
    short* G = (short*)&Foo[1]; // &0x4342

    return 0;
}
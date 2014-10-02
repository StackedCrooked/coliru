#include <iostream>
#include <cstring>


template<typename Derived>
struct Zeroed
{
protected:
    Zeroed() { memset(static_cast<Derived*>(this), 0, sizeof(Derived)); }
    ~Zeroed() {}
};



// Is this legal?
struct Item : Zeroed<Item> { int a, b, c; };


int main()
{
    std::cout << "Testing Zeroed<Item>" << std::endl;
    {
        for (int i = 0; i != 3; ++i)
        {
            Item item;
            std::cout << item.a << item.b << item.c << ' ';
            item.a = 1; item.b = 2; item.c = 3;
            std::cout << item.a << item.b << item.c << '\n';
        }
    }
    
    
    std::cout << "\nTesting non-zeroed" << std::endl;
    {
        struct Item { int a, b, c; };
        for (int i = 0; i != 3; ++i)
        {
            Item item;
            std::cout << item.a << item.b << item.c << ' ';
            item.a = 1; item.b = 2; item.c = 3;
            std::cout << item.a << item.b << item.c << '\n';
        }
    }
}


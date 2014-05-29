#include <iostream>

class HeapInteger
{
    static unsigned int instances;
    const unsigned int instance = ++instances;
    
    int* data;
    
    public:
    
    explicit HeapInteger(int initialData)
    {
        
        std::cout << "Constructing HeapInteger #" << instance << "." << std::endl;
        data = new int;
        set(initialData);
    }
    
    HeapInteger(const HeapInteger& other)
    {
        std::cout << "Copy-constructing HeapInteger #" << instance << " from HeapInteger #" << other.instance << "." << std::endl;
        data = new int;
        set(other.get());
    }
    
    ~HeapInteger()
    {
        std::cout << "Destructing HeapInteger #" << instance << "." << std::endl;
        delete data;
    }
    
    int get() const { return *data; }
    void set(int newData) { *data = newData; }
};

unsigned int HeapInteger::instances = 0;

HeapInteger foo()
{
    std::cout << "Inside foo()." << std::endl;
    HeapInteger h(123);
    return h;
}

int main()
{
    HeapInteger y(1);
    HeapInteger x(foo());
}
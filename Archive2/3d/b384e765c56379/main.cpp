#include <iostream>

class HeapInteger
{
    static unsigned int instances;
    const unsigned int instance = instances + 1;
    
    int* data;
    
    public:
    
    explicit HeapInteger(int initialData)
    {
        
        std::cout << "Constructing HeapInteger #" << instance << "." << std::endl;
        data = new int;
        set(initialData);
        instances++;
    }
    
    HeapInteger(const HeapInteger& other)
    {
        std::cout << "Copy-constructing HeapInteger #" << instance << " from HeapInteger #" << other.instance << "." << std::endl;
        data = new int;
        set(other.get());
        instances++;
    }
    
    HeapInteger(HeapInteger&& other)
    {
        std::cout << "Move-constructing HeapInteger #" << instance << " from HeapInteger #" << other.instance << "." << std::endl;
        data = other.data;
        other.data = nullptr;
        instances++;
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
    HeapInteger x(foo());
}
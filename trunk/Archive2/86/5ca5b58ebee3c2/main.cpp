#include <iomanip>
#include <iostream>


int global;

int& get()
{
    static int n;
    return n;
}


void print(int* n)
{
    union 
    {
        int* p;
        uint8_t bytes[sizeof(&n)];
    };
    
    p = n;
    
    for (int i = 0; i != sizeof(bytes); ++i)
    {
        // print as big-endian
        int ii = sizeof(bytes) - i - 1;
        std::cout << std::hex << std::setw(2) << std::setfill('0') << int(bytes[ii]) << ' ';
    }
    std::cout << std::dec << std::endl;
}





#define PRINT(var) std::cout << #var << '\t'; print(&var)

int main()
{
    PRINT(global);
    
    int stack;
    PRINT(stack);
    
    int& heap = *(new int());
    PRINT(heap);
    
    int& static_ = get();
    PRINT(static_);
}

#include <iostream>


struct Range
{
    template<unsigned N>
    Range(int (&arr)[N]) : b(arr), e(arr + N) {}
    
    Range(int* b, int* e) : b(b), e(e) {}
    
    auto size() const { return e - b; }    
    
    auto empty() const { return b == e; }
    
    auto begin() const { return b; }
    
    auto end() const { return e; }
    
    auto data() { return b; }
    
    auto data() const { return b; }
    
private:
    int* b;
    int* e;
};


int main()
{
    int data[10]{};
    
    for (auto&& i : Range(data))
    { 
        std::cout << i << ' ';
        i = &i - &data[0];
    }
    
    std::cout << std::endl;
    
    for (auto i : Range(data))
    { 
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

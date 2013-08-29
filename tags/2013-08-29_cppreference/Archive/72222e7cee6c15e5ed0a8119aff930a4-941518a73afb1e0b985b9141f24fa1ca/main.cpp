#include <array>
#include <iostream>
#include <vector>

template<typename T>
struct Array
{
    
    enum {
        sbo = 1024,
        max = sbo / sizeof(T)
    };
    Array(unsigned inSize = 0) :
        mSize(inSize),
        mSmallBuffer(),
        mBuffer(small() ? 0 : size())
    {
        std::cout << "small: " << small() << std::endl;
    }
    
    unsigned size() const { return mSize; }
    
    T* data() { return small() ? &mSmallBuffer[0] : mBuffer.data(); }
    const T* data() const { return small() ? &mSmallBuffer[0] : mBuffer.data(); }
    
    const T& operator[](unsigned i) const { return data()[i]; }
    T& operator[](unsigned i) { return data()[i]; }
    
    bool small() const
    {
        return size() < max;
    }
    
    unsigned mSize;
    std::array<T, max> mSmallBuffer;
    std::vector<T> mBuffer;
};


int main()
{
    Array<int> arr1(10);
    arr1[1] = 0;
    
    Array<int> arr2(1024);
    arr2[1] = 0;
}
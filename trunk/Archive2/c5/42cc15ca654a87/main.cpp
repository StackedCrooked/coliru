#include <iostream>

template<typename T>
void allocMemory(T *&data, const size_t numElems)
{
   #ifdef PINNED_MEMORY
      // allocate pinned memory
   #else
      data = new T[numElems];
   #endif   
}

template<typename T>
class MyVec
{
 T *data;
 size_t size;
public:
 MyVec(size_t _size): size(_size)
 { allocMemory<T>(data, size); } // gives VLA warning
 operator void*() { return data; }
 T& operator[](int i) { return data[i]; }
};


int main()
{
    MyVec<int> v(12);
    std::cout << v << "\n";
    std::cout << v[0] << "\n";
    std::cout << v[1] << "\n";
    return 0;
}

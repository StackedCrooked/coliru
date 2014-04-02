#include <vector>
#include <stdexcept>
#include <iostream>
#include <assert.h>


template<typename T>
struct Allocator : std::allocator<T>
{
    using std::allocator<T>::allocator;
};


namespace std
{
    template<typename T>
    class vector<T, std::allocator<T>> : public vector<T, Allocator<T>>
    {
    public:
        using vector<T, Allocator<T>>::vector;
    
        void push_back(T&& n)
        {
            if (this->size() == this->capacity())
            {
                throw std::logic_error("Realloc triggered! Your code is slow!");
            }
            vector<T, Allocator<T>>::push_back(std::move(n));
        }
    };
}



int main()
{
    std::vector<int> vec;
    vec.reserve(5);
    for (int i = 0; i != 10; ++i)
    {
        std::cout << vec.size() << "/" << vec.capacity() << std::endl;
        vec.push_back(1);
    }
}

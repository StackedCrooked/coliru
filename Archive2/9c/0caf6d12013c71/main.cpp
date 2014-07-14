#include <iostream>
#include <string>
#include <vector>


template<typename T>
struct delegate_allocator : std::allocator<T> {};


namespace std {


// specialization for std::vector<T, std::allocator<T>>
// this means that any std::vector<T> is hereby intercepted
// to avoid circular inheritance we have a delegate_allocator which simply inherits std::allocator
template<typename T>
class vector<T, std::allocator<T>> : public ::std::vector<T, delegate_allocator<T>>
{
public:
    using ::std::vector<T, delegate_allocator<T>>::vector;
    using typename ::std::vector<T, delegate_allocator<T>>::size_type;
    using typename ::std::vector<T, delegate_allocator<T>>::reference;
    using typename ::std::vector<T, delegate_allocator<T>>::const_reference;

    const_reference operator[](size_type n) const { return this->at(n); }
    reference operator[](size_type n) { return this->at(n); }
};


} // namespace std


int main()
{
    try
    {
        std::vector<int> vec;
        return vec[vec.size()]; // crash?
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "out_of_range: " << e.what() << std::endl;
    }
}

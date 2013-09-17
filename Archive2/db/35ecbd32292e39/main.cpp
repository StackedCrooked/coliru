#include <iostream>
#include <type_traits>
#include <string>
 
template<class T, std::size_t N>
class static_vector
{
    // propertly aligned uninitialized storage for N T's
    typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type data[N];
    std::size_t m_size;
public:
 
    static_vector() : m_size(0) {};
    // Create an object in aligned storage
    template<typename ...Args> void emplace_back(Args&&... args) 
    {
        new(data+m_size) T(std::forward<Args>(args)...);
        m_size++; // bounds check omitted
    }
 
    // Access an object in aligned storage
    const T& operator[](size_t pos) const 
    {
        return *static_cast<const T*>(static_cast<const void*>(&data[pos]));
    }
    // Delete objects from aligned storage
    ~static_vector() 
    {
        for(std::size_t pos = 0; pos < m_size; ++pos) {
            static_cast<const T*>(static_cast<const void*>(data+pos))->~T();
        }
    }
};
 
int main()
{
    static_vector<std::string, 10> v1;
    v1.emplace_back(5, '*');
    v1.emplace_back(10, '*');
    std::cout << v1[0] << '\n' << v1[1] << '\n';
}
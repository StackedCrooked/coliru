#include <iostream>
#include <vector>
#include <type_traits>
using namespace std;

const int ARRAY_SIZE = 100000000;

// http://stackoverflow.com/a/15975738/500104
template <class T>
class no_init_allocator
{
public:
    typedef T value_type;

    no_init_allocator() noexcept {}
    template <class U>
        no_init_allocator(const no_init_allocator<U>&) noexcept {}
    T* allocate(std::size_t n)
        {return static_cast<T*>(::operator new(n * sizeof(T)));}
    void deallocate(T* p, std::size_t) noexcept
        {::operator delete(static_cast<void*>(p));}
    template <class U>
        void construct(U*) noexcept
        {
            // libstdc++ doesn't know 'is_trivially_default_constructible', still has the old names
            static_assert(std::has_trivial_default_constructor<U>::value,
            "This allocator can only be used with trivally default constructible types");
        }
    template <class U, class A0, class... Args>
        void construct(U* up, A0&& a0, Args&&... args) noexcept
        {
            ::new(up) U(std::forward<A0>(a0), std::forward<Args>(args)...);
        }
};

int main() {
    //vector<char, no_init_allocator<char>> charArray(ARRAY_SIZE);
    char* charArray = new char[ARRAY_SIZE]; 
    for(int i = 0; i < ARRAY_SIZE; i++) {
        charArray[i] = (char)((i%26) + 48) ;
    }

    for(int i = 0; i < ARRAY_SIZE; i++) {
        charArray[i] = charArray[(i+1) % ARRAY_SIZE];
    }
}
#include <vector>

using std::size_t;

struct T
{
private:
    void* operator new(size_t);          // standard new
    void* operator new(size_t, void*);   // placement new
    void* operator new[](size_t);        // array new
    void* operator new[](size_t, void*); // placement array new
};

int main() { std::vector<T> v(1); }

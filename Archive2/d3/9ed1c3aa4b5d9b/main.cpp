#include <iostream>
#include <vector>

typedef struct {
    float *p;
    int n;
} float_array_C;

template<typename T> class MyArray : public T
{
public:
    MyArray(int n_init)
    {
        n = n_init;   
        contents.resize(n);
        p = contents.data();
    }       
private:
    std::vector<std::remove_pointer_t<decltype(T::p)>> contents;
};

int main()
{
return 0;
}
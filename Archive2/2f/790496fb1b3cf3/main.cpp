#include <vector>

template <typename T>
class A
{
public:
    void onlyForInts(T t)
    {
        // no-op
    }

protected:
    std::vector<T> myVector;
};

template<>
void A<int>::onlyForInts(int t)
{
    // works    
}

int main()
{
    A<int> i;
    i.onlyForInts(1); // works !

    A<float> f;
    f.onlyForInts(3.14f); // compiles, but does nothing !
}
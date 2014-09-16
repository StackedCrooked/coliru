#include <type_traits>  
#include <vector>

template <typename T>
class A
{
public:
    void onlyForInts(T t)
    {
        static_assert(std::is_same<T, int>::value, "This should work only with ints!");
    }

protected:
    std::vector<T> myVector;
};

int main()
{
    A<float> f;
	f.onlyForInts(3.14f); // does not compile !
}

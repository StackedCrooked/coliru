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
    A<int> i;
	i.onlyForInts(1); // works !
}

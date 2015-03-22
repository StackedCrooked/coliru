#include <vector>
#include <type_traits>

struct pod
{
    int i;
    float f;
    double d;
};

template<typename T>
struct vector
{
    std::vector<T> data;

    template<typename... Args, typename = typename std::enable_if<std::is_pod<T>::value>::type>
    void construct(T* where, Args&&... args)
    {
        T& t = *where;
        t = { args... };
    }


    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        data.resize(data.size() + 1);
        construct(&data.back(), std::forward<Args>(args)...);
    }
};

int main()
{
    vector<pod> pods;

    pods.emplace_back(1, 2.0f, 3.0);

}
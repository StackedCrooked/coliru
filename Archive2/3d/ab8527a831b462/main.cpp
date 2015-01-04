#include <stdexcept>
#include <string>

template<typename T>
class Multi
{
    template<int N, typename = void>
    struct A
    {
        static void myfun();
    };
};

template<typename T>
template<int N, typename U>
void Multi<T>::A<N, U>::myfun()
{}


template<typename T>
template <typename S>
struct Multi<T>::A<0, S>
{
    static int myfun()
        {
            return 34;
        }
};

template<typename T>
template <typename S>
struct Multi<T>::A<1, S>
{
    static std::string myfun();
};

template<typename T>
template<typename S>
std::string Multi<T>::A<1,S>::myfun()
{ return ""; }


int main()
{}
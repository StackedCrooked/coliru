#include <stdexcept>
#include <string>

template<typename T>
class Multi
{

template<int N, typename = void>
struct A
{
    static void myfun()
        {
            throw std::runtime_error("Wrong");
        }
};

};


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

template<>
template<>
int Multi<int>::A<0, void>::myfun()
{ return 0; }

int main()
{}
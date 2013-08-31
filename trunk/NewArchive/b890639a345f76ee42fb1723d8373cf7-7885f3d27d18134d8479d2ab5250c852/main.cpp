#include <iostream>
#include <string>
 
template <std::size_t Index, typename first, typename ...remaining>
struct type_at
{
    typedef typename type_at<Index - 1, remaining...>::type type;
};
 
template <typename first, typename ...remaining>
struct type_at<0, first, remaining...>
{
        typedef first type;
};
 
template <std::size_t Index, typename first, typename ...remaining>
struct value_at
{
        static typename type_at<Index, first, remaining...>::type 
        get(first First, remaining... args)
        {
                return value_at<Index - 1, remaining...>::get(args...);
        }
};
 
template <typename first, typename ...remaining>
struct value_at<0, first, remaining...>
{
        static first get(first First, remaining...)
        {
                return First;
        }
};
 
template <std::size_t Index, typename T, typename ...Args>
typename type_at<Index, T, Args...>::type
get(T t1, Args... args)
{
        return value_at<Index, T, Args...>::get(t1, args...);
}
 
 
int main()
{
        int   * a     = new int(10);
        double* b     = new double(3.14);
        std::string c = "But I'm a string :(";
 
        std::cout<< *get<0>(a, b, &c) <<"\n";
        std::cout<< *get<1>(a, b, &c) <<"\n";
        std::cout<< *get<2>(a, b, &c) <<"\n";
}

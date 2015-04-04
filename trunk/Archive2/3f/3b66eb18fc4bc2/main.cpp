#include <iostream>
#include <type_traits>

template<typename T>
struct get_impl {
    int operator()(int id)
    {
        return id-1;
    }
};


struct Tag1 {};
struct Tag2 {};
struct Tag3 {};



template<>
struct get_impl<Tag1> {
    int operator()(int id)
    {
        return id+1;
    }
};


template<>
struct get_impl<Tag2> {
    int operator()(int id)
    {
        return id+2;
    }
};


template<typename T>
int get(int id)
{
    return get_impl<T>{}(id);
}



int main()
{
    using std::cout;
    using std::endl;

    cout << get<Tag1>(0) << endl;
    cout << get<Tag2>(0) << endl;
    cout << get<Tag3>(0) << endl; // uses the generic get_impl()
}
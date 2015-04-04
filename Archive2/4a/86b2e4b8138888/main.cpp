#include <iostream>

struct Tag1 {};
struct Tag2 {};
struct Tag3 {};


int get_impl(int id, Tag1)
{
    return id+1;
}

int get_impl(int id, Tag2)
{
    return id+2;
}

template<typename T>
int get_impl(int id, T)
{
    return id-1;
}


template<typename T>
int get(int id)
{
    return get_impl(id, T{});
}



int main()
{
    using std::cout;
    using std::endl;

    cout << get<Tag1>(0) << endl;
    cout << get<Tag2>(0) << endl;
    cout << get<Tag3>(0) << endl; // uses the generic get_impl()
}
#include <iostream>
#include <string>
#include <vector>

using namespace std;


template<typename T0, typename T1>
struct my_pair{
    my_pair(T0 el0, T1 el1): el0(el0), el1(el1) {}
    T0 el0;
    T1 el1; // may be next pair
};


template<typename PairT>
auto get_my(PairT p, int i,  int current = 0) -> decltype( current == i ? p.el0 : p.el1 ){
    if (current == i){
        return p.el0;
    } else {
        return get_my(p.el1, i, current++);
    } 
}

template<typename T0, typename T1>
my_pair<T0, T1> make_my_pair(T0 el0, T1 el1){
    return my_pair<T0, T1>(el0, el1);
}



int main()
{
    my_pair<double, double> p1(12.789, 12.66);
    //auto p1 = make_my_pair(12.46, 12.66);
    //auto p2 = make_my_pair(p1, 12.66);
    
    auto el = get_my(p1, 0);
    cout<< el;
    return 0;
}

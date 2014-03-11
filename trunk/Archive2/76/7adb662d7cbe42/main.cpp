#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <type_traits>

using namespace std;


template<template<class...> class C, class F, class T, class... Tail>
C<typename result_of<F(T)>::type, Tail...>
transform(const C<T, Tail...>& in, F func)
{
  C<typename result_of<F(T)>::type, Tail...> out(in.size());
  std::transform(in.begin(), in.end(), out.begin(), func);
  return out;
}

int main ()
{
    vector<int> in = { 1, 2, 3 };
    list<double> in2 = {1.0, 2.0, 3.0};
    auto f0 = [](int val) { return val + 1; };
    auto f1 = [](int val) { return val > 1; };


    auto out0 = transform(in, f0);
    auto out1 = transform(in, f1);
    auto out2 = transform(in2, f1);

    for (auto i: out0)
        cout << i << endl;
    for (auto i: out1)
        cout << boolalpha << i << endl;
    for (auto i: out2)
        cout << boolalpha << i << endl;

}
#include <cstdlib>
#include <iostream>

using namespace std;

template <class T>
class Node{};

template <class T> class circList; //Forward declaration

template <class T>
class circIterator{};


template <class T>
class circList
{
    circIterator<T> add(T const& v, circIterator<T> itr); 
};

template <class T>
circIterator<T> circList<T>::add(T const& v, circIterator<T> itr)
{}

int main() {}
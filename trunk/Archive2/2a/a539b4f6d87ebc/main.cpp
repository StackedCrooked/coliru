#include <functional>
#include <iostream>

template<typename T, class COMP = std::less<T>> 
void insertionSort(T* elements, int size) {
    T tempElement;
    int j;
    COMP pred;
    for (int i = 0; i < size; ++i) {
        tempElement = elements[i];

        for (j = i - 1; j >= 0 && pred(tempElement, elements[j]); --j)
            elements[j + 1] = elements[j];

        elements[j + 1] = tempElement;
    }
}

template<template<typename> class E, typename T>
void insertionSort(T* element, int size)
{
    insertionSort<T, E<T>>(element, size);
}

int main(int argc, char *argv[]) {
  int A[] = {1,3,5,6,7,4,2};
  insertionSort<std::greater>(A, 7);
  for(auto i : A) std::cout << i << " ";
  std::cout << std::endl;
  int B[] = {1,3,5,6,7,4,2};
  insertionSort(B, 7);
  for(auto i : B) std::cout << i << " ";
  std::cout << std::endl;
}
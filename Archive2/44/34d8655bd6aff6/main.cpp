#include <iostream>
#include <type_traits>
#include <functional>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

// http://stackoverflow.com/questions/6376000/how-does-this-array-size-template-work

template <typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];
#define arraysize(array) (sizeof(ArraySizeHelper(array)))

template <typename T, size_t N> 
constexpr size_t array_size(const T (&)[N]) { return N; }

int main()
{
  char i[] = {1,2,3};
  cout << array_size(i) << endl;
}

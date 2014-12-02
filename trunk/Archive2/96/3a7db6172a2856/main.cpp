#include <iostream>
#include <string>
#include <vector>

int main()
{
// template type alias
template<class T> using ptr = T*; 
// the name 'ptr<T>' is now an alias for pointer to T
ptr<int> x;
}

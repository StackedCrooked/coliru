#include <algorithm>
#include <forward_list>
#include <iostream>
#include <iterator>

int main() 
{
     auto mylist = std::forward_list<int>{ 1, 2, 3, 4, 5 };
     mylist.remove(3);
     std::copy(begin(mylist), end(mylist), std::ostream_iterator<int>(std::cout, ","));
}

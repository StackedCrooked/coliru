// stl/lambda1.cpp
#include <algorithm>
#include <deque>
#include <iostream>
using namespace std;
int main()
{
deque<int> coll = { 1, 3, 19, 5, 13, 7, 11, 2, 17 };

int x = 5;
int y = 12;
auto pos = find_if (coll.cbegin(), coll.cend(), // range
[=](int i) { // search criterion
return i > x && i < y;
}
);
cout << "first elem >5 and <12: " << *pos << endl;
}
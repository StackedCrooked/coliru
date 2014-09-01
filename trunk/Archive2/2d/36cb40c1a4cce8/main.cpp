#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
 
using std::vector;

void foo(const vector<bool>&f ) {
    std::cout << f.size();
}
 
int main()
{
    int f[] = {1, 2, 3};
    foo({std::begin(f), std::end(f)});
}
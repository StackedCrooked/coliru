#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
#include <vector>
#include <boost/iterator/counting_iterator.hpp>

int func(int x)
{
 if (x==47)   
    return 6; 
 return 5;
 
}
using namespace std;
int main()
{
    int argmax = *std::max_element(boost::counting_iterator<int>(rand()%10), boost::counting_iterator<int>(std::numeric_limits<int>::max()), [](int a, int b){return func(a) < func(b);});
    cout << argmax << endl;   
}

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

int main(int argc, char *argv[])
{
    vector<int> v({ 1,2,1,1,2,2 });
    int val = 2;
    int ins = 3;

    // this is your actual algorithm
    v.reserve(v.size() + std::count(v.begin(), v.end(), val));
    for (std::vector<int>::iterator it = std::find(v.begin(), v.end(), val);
         it != v.end();
         it = std::find(v.insert(it+1, ins)+1, v.end(), val)
        ) {
            // dump each iteration to see what's happening
            std::copy(v.begin(), v.end(), std::ostream_iterator<int>(cout, " "));
            std::cout << std::endl;
        }
}

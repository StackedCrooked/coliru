#include <algorithm>
#include <iostream>
#include <string>
#include <boost/variant.hpp>

using namespace std;

int main(int argc, char* argv[])
{
    boost::variant<int, string> set[] = {1, 2, 3, "one", "two", "three"};

    size_t count = 0;
    do {
        cout << ++count << ": " 
             << set[0] << "," << set[1] << "," << set[2] << "," 
             << set[3] << "," << set[4] << "," << set[5] << endl;
    } 
    while(next_permutation(begin(set), end(set)));
    
    return 0;   
}

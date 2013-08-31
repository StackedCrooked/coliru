#include <iostream>
#include <thread>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<int> vec {1,2,3,4,5};
    
    for( auto& a : vec ) {
        cout << a << endl;
    }
    
    for( auto b = std::begin(vec) ; b != std::end(vec) ; ++b ) {
        auto&& a = *b;
        
        cout << a << endl;
    }
    return 0;
}
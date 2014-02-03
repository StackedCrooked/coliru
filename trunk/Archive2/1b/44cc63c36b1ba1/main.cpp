#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    string str = "Hello World!";
    
    srand(time(0));
    
    random_shuffle(begin(str), end(str));
    
    cout<<str<<endl;
    
    return 0;
}

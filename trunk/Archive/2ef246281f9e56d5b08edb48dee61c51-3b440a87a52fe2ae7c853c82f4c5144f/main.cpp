#include <iostream>
#include <bitset>

using namespace std;

int main(){
    long long truncator= 4294967551ll;
    cout<<truncator<<"\n";
    std::bitset<64> b(truncator);
    cout<<b;
    return 0;
}

#include <vector>
#include <iostream>

using namespace std;


template<typename T>
void flipem( vector<T>& vec )
{
    for( auto&& b : vec )
        b = !b;
}


int main()
{
    vector<bool> vb{ false, false, false };
    flipem(vb);
    for( auto b : vb ) cout << (int)b; cout << '\n';
    
    vector<char> vc{ false, false, false };
    flipem(vc);
    for( auto b : vc ) cout << (int)b; cout << '\n';
    
}

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;
bool ends_with(const string& s, const string& ending)
{
 return s.size() && std::search(s.rbegin(), s.rend(), ending.rbegin(), ending.rend())
        == s.rbegin();
    
}

int main()
{
    string one  = "ima.txtfile.txt";
    string two  = "imnota.txt.file";
    assert( ends_with(one,".txt"));
    assert(!ends_with(two,".txt"));
    assert(!ends_with("",".txt"));
    cout << "bye" ;

}

#include <iostream>
#include <vector>
using namespace std;

struct Empty {};
struct Bit {unsigned bit:1; };

int main()
{
    Empty e;
    int q[10];
    vector <int> v = {1,2,3,4,5,6,7,8,9,10};
    
    cout << "size of empty class: "     << sizeof e        << '\n'
              << "size of pointer : "        << sizeof &e       << '\n'
              << "sizeof int[10]: " << sizeof(int[10]) << '\n'
              << "sizeof q: " << sizeof(q) << endl
              << "sizeof v: " << sizeof(v) << endl            
              << "alignof q: " << alignof(vector <int>) << endl            
              << "alignof v: " << alignof(int [10]) << endl            
           
              ;
}
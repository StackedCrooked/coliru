#include <string> 
#include <iostream> 
#include <bitset>
#include <climits>
using namespace std; 

template<typename T>
void show_binrep(const T& a)
{
    const char* beg = reinterpret_cast<const char*>(&a);
    const char* end = beg + sizeof(a);
    while(beg != end)
        std::cout << std::bitset<CHAR_BIT>(*beg++) << ' ';
    std::cout << '\n';
}


int main()
{
    char a;
   
    a = -58;
  
    show_binrep(a);
  
        
    string SS;     // C++ STL string 
    SS = "pippo"; 
    cout << SS << endl; 
    cout << "this is the binary representation of the string: " << SS << endl;
    show_binrep(SS);
    
    
}
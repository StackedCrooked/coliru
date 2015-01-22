#include <iostream>
using namespace std;
class c{  int a;
public : c() {} 
 c(const c&); 
 c& operator =(c&); };  
c& c::operator=(c &c){ cout << endl << "copiere cu egal"; return c;} 
c::c(const c &c) { cout << endl << "Constructor de copiere"; } 
int main() 
{ c x,y=x; 
 c b=x; x=y; 
}

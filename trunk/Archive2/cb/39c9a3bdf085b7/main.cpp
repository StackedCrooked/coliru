#include <iostream>
#include <sstream>

int main()
{
    using namespace std;
    
    ostringstream s;
    s << "13.3( ',gate";
    
    cout << s.str().c_str() << endl;    
}

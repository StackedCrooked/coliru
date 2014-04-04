#include <iostream>
#include <memory>

using namespace std;

int main()
{

    shared_ptr<string> s;
    { 
        auto p = shared_ptr<string>(new string("shared"));
        cout << *p << endl; 
        cout << "is p unique? " << boolalpha << p.unique() << endl; 
        s = p; 
        cout << "is p unique? " << boolalpha << p.unique() << endl; 
        cout << "is s unique? " << boolalpha << s.unique() << endl; 
    } // Speicher wird am Ende dieses Blocks NICHT frei gegeben
    
    cout << "is s unique? " << boolalpha << s.unique() << endl; 
    cout << *s << endl;
   
   return 0;
}

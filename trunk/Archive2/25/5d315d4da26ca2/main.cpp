#include <map>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

bool initialize();

template <typename T>
struct X {
    vector<int>  d;
    
    static X* instance() {
        static X *p =  new X();
        return p; 
    }

    int value() const {
        return d.size(); 
    }
    
    void store(int x)
    { 
        cout << "storing " << x<<endl;
        d.push_back(x); 
    }
    
    static int get() {  
        static bool dummy = initialize();
        if (dummy || 1) ;
        return instance()->value();
    }
};

bool l_initialize() {
    cout << "initialize" << endl;
    
    X<int>::instance()->store(10);
    X<double>::instance()->store(10);
    X<double>::instance()->store(20);

    return true;
}

bool initialize() {
    
    static auto once = l_initialize();
    return once;
}

int main()
{
    cout <<"int: " <<  X<int>::get() << endl;
    cout <<"double: " <<  X<double>::get() << endl;
    cout <<"int: " <<  X<int>::get() << endl;
}
#include <iostream>
using namespace std;
    struct SO{ SO(){ cout << "SO()" << endl; } };
    struct SSO{ SSO(){ cout << "SSO()" << endl; } };
    
        struct O
        {
            O(){ cout << "O()" << endl; }
            SO so;
            SSO sso;
        };
    int main()
    {
        O o = *(new O);
    }
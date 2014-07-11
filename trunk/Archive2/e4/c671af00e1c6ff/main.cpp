#include <iostream>
#include <string>
using namespace std;

class X{
    public:
        int* p{};
        int size{};
        X(){}
        X(int n) : size(n){
            p = new int[n];
            for(int i = 0; i < n; i++)
                p[i] = i;
            cout << "Constructor\n";
        }
        ~X(){
            delete[] p;
        }
        X(const X& r){
            cout << "Copy\n";

        }
        X(X&& r){
            p = r.p;
            size = r.size;
            r.p = NULL;
            r.size = 0;
            cout << "Move\n";
        }
};
int main() {
    X a(10); //constructor    
    X b(a); // copy
    X c(X(3)); //constructor, move
    return 0;
}

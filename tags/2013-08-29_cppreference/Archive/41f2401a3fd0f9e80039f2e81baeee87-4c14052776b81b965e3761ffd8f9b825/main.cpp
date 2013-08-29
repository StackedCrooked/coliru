#include <iostream>

using namespace std;



int main(){
    char c='4';
    const char *b;
    int i,j;
    i=atoi(string(1,c).c_str());
    b=string(1,c).c_str();
    j=atoi(b);
    cout<<i<<" "<<j<<endl;    
}

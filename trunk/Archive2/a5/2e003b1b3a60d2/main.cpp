#include <iostream>
#include <string>
#include <vector>
#include <string>


//void myfunc(const std::string& s, int i, int n);

void ciao(const std::string& s, int i, int n){
     if (i<n){
            ciao(s,i+1,n);
            std::cout << s[i];
         }
}

int main()
{
    std::string thnx = "noril ,sknaht";
    ciao(thnx,0,thnx.length());
return 0;
}

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
string RandomString(int len)
{
   srand(time(0));
   string str = "$A&*@#%*C0123%!$@456789A*&*BCDEFG&*&HIJKLMN#@*&OPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
   int pos;
   while(str.size() != len) {
    pos = ((rand() % (str.size() - 1)));
    str.erase (pos, 1);
    
    
   }
   return str;
}

int main()
{
   string random_str = RandomString(8);
   cout << "random_str : " << random_str << endl;
}
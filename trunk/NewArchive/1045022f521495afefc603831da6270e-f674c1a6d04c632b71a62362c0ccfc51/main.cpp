
#include <iostream>

using namespace std;

int abs(int i)
{
    return (0 < i) ? i : -i;
}

int main()
{
   auto i = 100;
   string s = "I am a string";
   
   cout << i << endl;
   cout << s << endl;
   return 0;
}

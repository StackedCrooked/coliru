#include <iostream>
#include <string>
using namespace std;

class Uno
{
  public:
    
    string text = "X";
    
    Uno()
    {
        cout << text;
    }
 
    
    Uno(const Uno &o)
    {
        text = o.text;
        cout << text;
    }
};



    int main()
    {
            Uno u;
            u.text = "Y";
            Uno k=u;

            return 0;
    }
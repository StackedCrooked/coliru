#include <iostream>
#include <cstring>
using namespace std;
class Complex {
private:
double r,i;
public:
    Complex& operator=(const char* str)
    {
            int k=0;
            r = 0;
            i = 0;
            for(;str[k] != '+';k++)
                   r = r*10 + int(str[k] - '0');
            k++;
            for(;str[k] != 'i';k++)
                   i = i*10 + int(str[k] - '0');
            return *this;
    }

    void Print() 
    {
        cout << r << "+" << i << "i" << endl;
    }
};
int main()
{
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}
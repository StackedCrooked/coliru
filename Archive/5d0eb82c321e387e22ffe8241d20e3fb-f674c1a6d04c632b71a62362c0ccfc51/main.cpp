#include <iostream>
#include <string>
#include <vector>


void inc(int &a)
{

}



int main()
{
    int aa;
    inc(aa); //valid
    
    int &a = aa; // points to something
    inc(a); //valid
}

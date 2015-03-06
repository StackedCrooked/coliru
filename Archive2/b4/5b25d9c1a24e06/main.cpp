#include <string>
#include <iostream>
 
int main()
{
    std::string a = "(abC)";
    int start  = 0;
    int length = a.length();
    
    if(a[length-1] == ')') {
        --length;
    }
    if (a[0] == '(') {
        start++;
        length--;
    }

    

    std::cout << a.substr(start,length) << std::endl;
    
    return 0;

}
#include <string>
#include <iostream>
 
int main()
{
    std::string a = "2014-09-12 14:46:27.000";
    const char* mon_table[] = { "Jan", "Feb", "Mar" , "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};


 
    std::string y = a.substr(0,4);
    std::cout << y << '\n';
 
    std::string m = a.substr(5, 2);
    std::cout << m << '\n';
    int month = atoi(m.c_str());
    std::cout<<month<<'\n';
 
    std::string d = a.substr(8, 2);
    std::cout << d << '\n';
    
    std::string h = a.substr(11,2);
    std::string mi = a.substr(14,2);
    std::string s = a.substr(17,2);
    std::cout<<h<<'\n';
    std::cout<<mi<<'\n';
    std::cout<<s<<'\n';
    
    std::string finalDate = d + "-" + mon_table[month-1] + "-" + y + " " + h + ":" + mi;
    std::cout<<finalDate<<'\n';
    
 
   
}
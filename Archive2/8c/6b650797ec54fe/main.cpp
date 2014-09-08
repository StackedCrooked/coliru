#include <locale>
#include <iostream>

class Date
{
    int mo, da, yr;
public:
    Date(int m, int d, int y)
    {
        mo = m; da = d; yr = y;
    }
    friend std::ostream& operator<<(std::ostream& os, const Date& dt);
};

std::ostream& operator<<(std::ostream& os, const Date& dt)
{
   std::time_base::dateorder d = std::use_facet<std::time_get<char>>(os.getloc()).date_order();
    if (d == std::time_base::dmy)
    {
        os << dt.da << '/' << dt.mo << '/' << dt.yr;
    }
    else if (d == std::time_base::mdy)
    {
        os << dt.mo << '/' << dt.da << '/' << dt.yr;
    }
    else
    {
        os << dt.yr << '/' << dt.mo << '/' << dt.da;
    }
    return os;
}

int main()
{
    Date d{ 9, 8, 2014 };
    std::cout.imbue(std::locale("en_US.utf8"));
	std::cout << d;
    
    std::cout << std::endl;
	
	std::cout.imbue(std::locale("de_DE.utf8"));
	std::cout << d;
    std::cout << std::endl;
}

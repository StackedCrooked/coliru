#include <iostream>
#include <string>
#include <ostream>
#include <sstream>
#include <iterator>
#include <iomanip>

#include <boost/format.hpp>

void getDateTime(int &y, int &m, int &d, int &hh, int &mm, int &ss) {
    y = 2013;
    m = 07;
    d = 25;
    hh = 14;
    mm = 34;
    ss = 12;
}

std::string use_stringstream() {
    int ss, mi, hh, dd, mm, yyyy;
	getDateTime(yyyy, mm, dd, hh, mi, ss);
	std::ostringstream ostr;
	using std::setw;
	ostr.fill('0');
	ostr << "to_date('" << setw(2) << dd << setw(1) << '/' << setw(2) << mm << setw(1) << '/' << setw(4) << yyyy 
			 << setw(1) << ' ' << setw(2) << hh << setw(1) << ':' << setw(2) << mi << setw(1) << ':' << setw(2) << ss 
			 << "','DD/MM/YYYY HH24:MI:SS')";
	return ostr.str();
}

std::string use_bformat() {
    int ss, mi, hh, dd, mm, yyyy;
    getDateTime(yyyy, mm, dd, hh, mi, ss);
    
    return str(boost::format("to_date('%02d/%02d/%04d %02d:%02d:%02d','DD/MM/YYYY HH24:MI:SS')") % dd % mm % yyyy % hh % mi % ss);
}

int main()
{
    std::cout << use_stringstream() << std::endl;
    std::cout << use_bformat() << std::endl;
}

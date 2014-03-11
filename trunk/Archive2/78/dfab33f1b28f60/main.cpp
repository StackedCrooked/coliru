#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using boost::is_any_of;
using boost::split;

using std::string;
using std::vector;

class Version {
public:
	explicit					Version		(const std::string &version)
    {
        std::cout << "version: " << version.c_str() << std::endl;
        split(m_parts, version, is_any_of("."));
    }

	bool						operator==	(const Version &that) const;
	bool						operator!=	(const Version &that) const;
	bool						operator< 	(const Version &that) const;
	bool						operator> 	(const Version &that) const;
	bool						operator<=	(const Version &that) const;
	bool						operator>=	(const Version &that) const;

private:
	static int					compare		(	const Version &lhs,
												const Version &rhs)
    {
        const vector<string> &					lhsParts	= lhs.m_parts;
    	const vector<string> &					rhsParts	= rhs.m_parts;
    
    	vector<string>::const_iterator			lhsPart		= lhsParts.begin();
    	vector<string>::const_iterator			rhsPart		= rhsParts.begin();
    
    	const vector<string>::const_iterator &	lhsEnd		= lhsParts.end();
    	const vector<string>::const_iterator &	rhsEnd		= rhsParts.end();
    
    	while (lhsPart != lhsEnd && rhsPart != rhsEnd) {
    		unsigned	lhsNumber	= boost::lexical_cast<unsigned>(*lhsPart);
    		unsigned	rhsNumber	= boost::lexical_cast<unsigned>(*rhsPart);
    		int			comparison	= lhsNumber - rhsNumber;
    
    		if (0 == comparison)
    			comparison = lhsPart->compare(*rhsPart);
    
    		if (0 != comparison)
    			return comparison;
    
    		++lhsPart;
    		++rhsPart;
    	}

	    return	lhsPart != lhsEnd ? +1 :
		    	rhsPart != rhsEnd ? -1 : 0;
    }

	std::vector<std::string>	m_parts;
};


//	Implementation


inline bool Version::operator==	(const Version &that) const { return compare(*this, that) == 0; }
inline bool Version::operator!=	(const Version &that) const { return compare(*this, that) != 0; }
inline bool Version::operator< 	(const Version &that) const { return compare(*this, that) <  0; }
inline bool Version::operator> 	(const Version &that) const { return compare(*this, that) >  0; }
inline bool Version::operator<=	(const Version &that) const { return compare(*this, that) <= 0; }
inline bool Version::operator>=	(const Version &that) const { return compare(*this, that) >= 0; }

int main()
{
    Version v1("1.0");
    Version v2("1.0.1");
    Version v3("1.0.2");
    Version v4("1.0.3");
    Version v5("1.0.3.1");
    Version v6("1.0.4");
    
    if (v1 < v5){ std::cout << "TRUE1" << std::endl; }
    if (v5 < v6){ std::cout << "TRUE2" << std::endl; }
    if (v5 != v6){ std::cout << "TRUE3" << std::endl; }
    if (v6 > v5){ std::cout << "TRUE4" << std::endl; }
}

#include <string>
#include <sstream>
#include <iostream>
#include <ostream>
#include <cassert>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/access.hpp>

struct CXMLList {
    std::string Name;
	int Param;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & BOOST_SERIALIZATION_NVP(Name);
		ar & BOOST_SERIALIZATION_NVP(Param);
	}
};

int main(int argc, char* argv[]) {
	std::ostringstream ofs;
	boost::archive::xml_oarchive oa(ofs);
	CXMLList xmllist;
	xmllist.Name = "Name";
	xmllist.Param = 1;
	oa << BOOST_SERIALIZATION_NVP(xmllist);
    std::cout << "XML is:" << std::endl;
	std::cout << ofs.str() << std::endl;
	return 0;
}

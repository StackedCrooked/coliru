
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/serialization.hpp>
#include <iostream>

int main () {
    boost::archive::text_oarchive ar(std::cout);
	ar << std::make_pair(1, 2);
}

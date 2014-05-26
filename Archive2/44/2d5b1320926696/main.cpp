#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/version.hpp>

struct Foo {
   std::list<std::string> data;
   
   template<class Archive>
   void serialize(Archive& ar, unsigned int /*version*/) {
      ar & data;
   }
};

int main() {
   std::cout << "Boost version " << BOOST_LIB_VERSION << '\n';

   Foo a;
   a.data.push_back("much longer than 7 chars");
   a.data.push_back("also longer than 7 chars");
   a.data.push_back("another reasonably long string");

   std::ostringstream os;
   {
      boost::archive::text_oarchive oa(os);
      oa << a;
   }

   Foo b;
   {
      const std::string s = os.str();
      boost::iostreams::filtering_istream is(boost::iostreams::array_source(&*s.begin(), &*s.end()));
      boost::archive::text_iarchive ia(is);
      ia >> b;
   }

   if (a.data == b.data)
      std::cout << "serialization success\n"; 
   else
      std::cout << "serialization failure\n"; 

   return 0;
}

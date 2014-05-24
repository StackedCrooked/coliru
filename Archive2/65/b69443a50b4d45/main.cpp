#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/serialization/access.hpp>
#include <boost/version.hpp>

struct Foo {
   unsigned long long bar[3];
   
   template<class Archive>
   void serialize(Archive& ar, const unsigned int /*version*/) {
      ar & bar;
   }
};

std::ostream& operator<<(std::ostream& os, const Foo& foo) {
   return os << foo.bar[0] << ' ' << foo.bar[1] << ' ' << foo.bar[2];
}

int main() {
   std::cout << "Boost version " << BOOST_LIB_VERSION << '\n';
   
   Foo before;
   before.bar[0] = 0;
   before.bar[1] = 1;
   before.bar[2] = 2;

   std::cout << "before: " << before << '\n';

   std::string buffer;
   {
      boost::iostreams::filtering_ostream os(boost::iostreams::back_inserter(buffer));
      boost::archive::text_oarchive oa(os);
      oa << before;
   }

   Foo after;
   {
      boost::iostreams::filtering_istream is(boost::make_iterator_range(buffer.begin(), buffer.end()));
      boost::archive::text_iarchive ia(is);
      ia >> after;
   }

   std::cout << "after: " << after << '\n';

   return 0;
}

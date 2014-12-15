#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <iostream>
#include <sstream>

namespace ser = boost::serialization;
namespace archive = boost::archive;

class Person
{
public:
   Person() {}
   Person(int a) : age(a)
   {
   }
   bool operator == (const Person& rhs) const
   {
      return age == rhs.age;
   }
private:
   friend class boost::serialization::access;

   template<typename Archive>
   void serialize(Archive& a, unsigned int)
   {
      a & age;
   }

   int age;
};

int main()
{
   const size_t n = 10;
   Person** persons = new Person*[n];
   for (size_t i = 0; i < n; ++i)
   {
      persons[i] = new Person(i + 10);
   }
   std::stringstream ss;
   archive::binary_oarchive oa(ss);
   oa << n;
   for (size_t i = 0; i < n; ++i)
   {
      oa << persons[i];
   }
   size_t loaded_size = 0;
   archive::binary_iarchive ia(ss);
   ia >> loaded_size;
   Person** loaded = new Person*[loaded_size];
   for (size_t i = 0; i < loaded_size; ++i)
   {
      ia >> loaded[i];
   }
   std::cout << (*loaded[0] == *persons[0] && *loaded[loaded_size - 1] == *persons[n - 1]) << std::endl;
   for (size_t i = 0; i < n; ++i)
   {
      delete persons[i];
   }
   delete persons;
   for (size_t i = 0; i < loaded_size; ++i)
   {
      delete loaded[i];
   }
   delete loaded;
}

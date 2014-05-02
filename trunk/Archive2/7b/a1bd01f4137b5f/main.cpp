#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp> 
#include <boost/serialization/shared_ptr.hpp>
#include <sstream>

struct A
{
public:
   std::string oldname;
   std::string newname;

   friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive &ar, const unsigned int version)
      {
         ar & oldname;
         ar & newname;
      }
};

struct Example
{
public:
   bool check;
   std::map<std::string, boost::shared_ptr<A> > mapOfA;

   private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive &ar, const unsigned int version)
      {
         ar & check;
         ar & mapOfA;
      }
};

void set_data(boost::shared_ptr<A> e)
{
    e->oldname="a";
    e->newname="b";
}

void set_data(Example &e)
{
   e.check=false;

   // to initialize e.mapOfA
   boost::shared_ptr<A> a1 (new A());
   set_data(a1);
   e.mapOfA.insert(std::make_pair("a",a1));
}

void compare_data(std::map<std::string,boost::shared_ptr<A>> const& e1,std::map<std::string,boost::shared_ptr<A>> const& e2)
{
    assert(0 == std::lexicographical_compare(
            e1.begin(), e1.end(),
            e2.begin(), e2.end()));
   // because it is of type map, it may be not in proper order   
   typedef std::map<std::string,boost::shared_ptr<A>>::const_iterator i1;

   i1 e1_i1= e1.begin();
   i1 e2_i1 =e2.begin();

   while ( e1_i1 != e1.end() && e2_i1 != e2.end()) 
   {
      assert( e1_i1->first == e2_i1->first);

      const std::string &key = e1_i1->first;
      e2_i1 =e2.find(key);
      assert(e1_i1->second == e2_i1->second);

      e1_i1++;
      e2_i1++;
    }
}

void compare_data(Example const& e1,Example const& e2)
{
   assert(e1.check == e2.check);

   // need to compare e1->mapOfA with e2->mapOfA
   compare_data(e1.mapOfA, e2.mapOfA);
}

int main()
{
   std::stringstream ss; 
   {
       Example c;
       set_data(c);
       boost::archive::text_oarchive oa(ss);
       oa << c;
   }

   std::cout << ss.str() << "\n";

   {
       ss.seekg(0ul);
       boost::archive::text_iarchive ia(ss);

       Example d;
       ia >> d;

       std::stringstream roundtrip_ss;
       boost::archive::text_oarchive oa(roundtrip_ss);
       oa << d;

       std::cout << roundtrip_ss.str() << "\n";
       //compare_data(c,d); 
   }
}

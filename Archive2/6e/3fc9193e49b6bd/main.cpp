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
   std::map<std::string,boost::shared_ptr<A>> Atype;

   private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive &ar, const unsigned int version)
      {
         ar & check;
         ar & Atype;
      }
};

void set_data(boost::shared_ptr<A> e)
{
    e->oldname="a";
    e->newname="b";
}

void set_data(Example *e)
{
   e->check=false;

   // to initialize e->Atype
   boost::shared_ptr<A> a1 (new A());
   set_data(a1);
   e->Atype.insert(std::make_pair("a",a1));
}

void compare_data(std::map<std::string,boost::shared_ptr<A>> e1,std::map<std::string,boost::shared_ptr<A>> e2)
{
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

void compare_data(Example *e1,Example *e2)
{
   assert(e1->check == e2->check);

   // need to compare e1->Atype with e2->Atype
   compare_data(e1->Atype,e2->Atype);
}

int main()
{
   boost::archive::text_oarchive ao(std::cout);

   Example c;
   set_data(&c);

   const Example & oc=c;
   ao << oc;

   std::stringstream ss; 
   boost::archive::text_oarchive oa(ss);
   oa << oc;

   boost::archive::text_iarchive ia(ss);

   Example d;
   ia >> d;

   compare_data(&c,&d); 

}
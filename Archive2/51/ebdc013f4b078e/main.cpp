#include <boost/any.hpp>
#include <boost/function.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <iostream>
#include <string>

struct person
{
  person(std::string name,std::string surname,int birth_year,std::string craft):
    name(name),surname(surname),birth_year(birth_year),craft(craft){}

  std::string name;
  std::string surname;
  int birth_year;
  std::string craft;
}; 

typedef std::function<boost::any(const person&)>                any_person_extractor;
typedef std::function<bool (const boost::any,const boost::any)> any_compare;

struct void_person_extractor
{
  typedef boost::any result_type;
  result_type operator()(const person&)const{return boost::any();}
};

template<typename T>
struct any_less
{
  bool operator()(const boost::any& x,const boost::any& y)const
  {
    return boost::any_cast<T>(x)<boost::any_cast<T>(y);
  }
  bool operator()(const boost::any& x,const T& y)const
  {
    return boost::any_cast<T>(x)<y;
  }
  bool operator()(const T& x,const boost::any& y)const
  {
    return x<boost::any_cast<T>(y);
  }
};

template<>
struct any_less<void>
{
  bool operator()(const boost::any& x,const boost::any& y)const{return false;}
};

int main()
{
  using namespace boost::multi_index;

  typedef multi_index_container<
    person,
    indexed_by<
      ordered_non_unique<
        composite_key<
          person,
          any_person_extractor,
          any_person_extractor,
          any_person_extractor,
          any_person_extractor
        >,
        composite_key_compare<
          any_compare,
          any_compare,
          any_compare,
          any_compare
        >
      >
    >
  > person_container;
  
  person_container c(
    boost::make_tuple(
      boost::make_tuple(
        boost::make_tuple(
          any_person_extractor(member<person,int,&person::birth_year>()),
          any_person_extractor(member<person,std::string,&person::name>()),
          any_person_extractor(member<person,std::string,&person::surname>()),
          void_person_extractor()
        ),
        boost::make_tuple(
          any_less<int>(),
          any_less<std::string>(),
          any_less<std::string>(),
          any_less<void>()
        )
      )
    ));
    
  c.insert(person("Smith","John",1970,"writer"));
  c.insert(person("Brown","Rose",1980,"dancer"));
  c.insert(person("Gonzalez","Adolfo",1955,"cook"));
  c.insert(person("Conrad","Mary",1959,"surgeon"));
  c.insert(person("Abramovitch","Ron",1959,"basketball player"));
    
  for(person_container::iterator it=c.begin(),it_end=c.end();it!=it_end;++it){
    std::cout<<it->name<<", "<<it->surname<<", "<<it->birth_year<<", "<<it->craft<<"\n";
  }
  
  int birth_year=1959;
  std::pair<person_container::iterator,person_container::iterator> p=c.equal_range(birth_year);
  std::cout<<"\nBorn "<<birth_year<<":\n";
  for(;p.first!=p.second;++p.first){
    std::cout<<p.first->name<<", "<<p.first->surname<<", "<<p.first->craft<<"\n";
  }
}

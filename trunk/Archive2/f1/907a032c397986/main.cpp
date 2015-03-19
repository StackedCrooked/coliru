// transform algorithm example
#include <iostream>     // std::cout
#include <boost/format.hpp>
#include <sstream>
#include <iterator>
#include <set>
#include <boost/bind.hpp>

struct Age
{
 Age(int i) {integerAge=i; };
 int integerAge;
 bool operator==(const Age& rhs) const { return this->integerAge==rhs.integerAge; };
 //bool operator!=(const Age& rhs) const { return this->integerAge!=rhs.integerAge; }; not availabe
 bool operator<(const Age& rhs) const {return this->integerAge<rhs.integerAge;};
};

struct Person
{
    Person(int i,std::string n) {m_i=i; this->name=n;};
    bool operator==(const Person& rhs) const { return this->m_i==rhs.m_i; };
    bool operator<(const Person& rhs) const {return this->m_i<rhs.m_i;};
    Age GetAge() { return Age(m_i); };
    friend std::ostream& operator<<(std::ostream& oss, const Person& id);
    private:
    int m_i;
    std::string name;
};

std::ostream& operator<<(std::ostream& oss, const Person& id)
{
    return oss<<"Name: "<<id.name << "Age:"<<id.m_i<<"\n";
}

int main () {

  Person a(42,"a");
  Person b(43,"b");
  Person c(35,"c");
  Person d(33,"d");
  std::vector<Person> v;
  v.push_back(a);
  v.push_back(b);
  v.push_back(c);
  v.push_back(d);
  
  std::vector<Person> ageof35;
  std::sort(ageof35.begin(),ageof35.end());
  
  //std::copy_if(v.begin(),v.end(),std::back_inserter(ageof35),boost::bind(&Person::GetAge,_1)==35); not available in c++03
  std::remove_copy_if(v.begin(), v.end(), std::back_inserter(ageof35),boost::bind(&Person::GetAge,_1)!=35);
  std::copy(ageof35.begin(), ageof35.end(), std::ostream_iterator<Person>(std::cout));
  
  return 0;
}

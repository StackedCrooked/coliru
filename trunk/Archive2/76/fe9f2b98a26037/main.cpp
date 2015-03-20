// transform algorithm example
#include <iostream>     // std::cout
#include <iterator>
#include <vector>
#include <map>
#include <boost/bind.hpp>
#include <utility>


struct Person
{
    Person(int i,std::string n) {Age=i; this->name=n;};
    //bool operator==(const Person& rhs) const { return this->Age==rhs.Age; };
    //bool operator<(const Person& rhs) const {return this->Age<rhs.Age;};
    int GetAge() { return this->Age; };
    std::string GetName() { return this->name; };
    friend std::ostream& operator<<(std::ostream& oss, const Person& id);
    private:
    int Age;
    std::string name;
};

std::ostream& operator<<(std::ostream& oss, const Person& id)
{
    return oss<<"Name: "<<id.name << "Age:"<<id.Age<<"\n";
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
  
  
  //std::vector<int> ages;
  //std::transform(v.begin(),v.end(),std::inserter(ages,ages.end()),boost::bind(&Person::GetAge,_1));
  
  std::map<std::string,int>persons;
  //std::transform(v.begin(),v.end(),std::inserter(persons,persons.end()), std::make_pair<std::string,int>(boost::bind(&Person::GetName,_1)),(boost::bind(&Person::GetAge,_1)));
  
  //std::copy (ages.begin(),ages.end(),std::ostream_iterator<int>(std::cout));
  
  return 0;
}

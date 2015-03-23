#include <string>
using std::string;

class Dog {
     protected:
         string m_name;
         int m_age; 
     public:
         Dog(const Dog& d) { m_name = d.getName(); m_age = d.getAge(); }
         string getName() { return m_name; }
         int getAge() { return m_age; }
};
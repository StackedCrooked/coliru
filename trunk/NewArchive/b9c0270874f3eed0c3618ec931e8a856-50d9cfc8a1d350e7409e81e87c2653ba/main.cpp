#include <iostream>
#include <vector>
#include <set>
#include <list>



struct Tracer {
   Tracer(void)
      :m_name("(none)")
   {
      std::cout << "[" << m_name << "]    " << __PRETTY_FUNCTION__ << std::endl;
   }
   Tracer(const std::string & name)
      :m_name(name)
   {
      std::cout << "[" << m_name << "]    " << __PRETTY_FUNCTION__ << std::endl;
   }
   Tracer(const Tracer & other)
      :m_name(other.m_name)
   {
      std::cout << "[" << m_name << "]    " << __PRETTY_FUNCTION__ << std::endl;
   }
   Tracer(const Tracer && other)
      :m_name(other.m_name)
   {
      std::cout << "[" << m_name << "]    " << __PRETTY_FUNCTION__ << std::endl;
   }
   Tracer & operator=(const Tracer & other) {
      m_name = other.m_name;
      std::cout << "[" << m_name << "]    " << __PRETTY_FUNCTION__ << std::endl;
      return *this;
   }
   Tracer & operator=(const Tracer && other) {
      m_name = other.m_name;
      std::cout << "[" << m_name << "]    " << __PRETTY_FUNCTION__ << std::endl;
      return *this;
   }
   ~Tracer() {
      std::cout << "[" << m_name << "]    " << __PRETTY_FUNCTION__ << std::endl;
   }

   std::string m_name;
};


class MyClass {
    std::vector<Tracer> V;   
public:
    MyClass() : V(3) {};
    std::vector<Tracer> getV(){ return V; }
};

int main (void)
{
using std::cout;
using std::endl;
    MyClass obj;
    
    size_t i, size;
    size = obj.getV().size();
    Tracer sum;
    cout << "starting loop"<< endl;
    for(size_t i = 0; i < size; i++){
        sum = obj.getV().at(i);
    }
    cout << "Ending loop"<< endl;
}


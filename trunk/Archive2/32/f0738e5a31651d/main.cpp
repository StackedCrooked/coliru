#include <string>
#include <iostream>
#include <boost/variant.hpp>

using my_variants = boost::variant<int, std::string>;

using namespace std;

class value {
public:

  value(const my_variants &value) : m_value(value) {}


  my_variants get() const {
    return m_value;
  }

  void set(const my_variants &value) {
    m_value = value;
  }

private:
  my_variants m_value;
};


int main(int argc, char* argv[]) {
  std::vector<value> vals;
    
  vals.push_back(value(int(123)));
  vals.push_back(value(string("abc")));
  vals.push_back(value(int(987)));
  vals.push_back(value(string("zyx")));
    
  std::cout << boost::get<int>(vals[0].get()) << "\n";
  std::cout << boost::get<string>(vals[1].get()) << "\n";
  std::cout << boost::get<int>(vals[2].get()) << "\n";
  std::cout << boost::get<string>(vals[3].get()) << "\n";
  
  auto tmp = vals[0].get();
  
  vals[0].set(vals[1].get());
  vals[1].set(vals[2].get());
  vals[2].set(vals[3].get());
  vals[3].set(tmp);
  
  std::cout << "after shift:\n";
  std::cout << boost::get<string>(vals[0].get()) << "\n";
  std::cout << boost::get<int>(vals[1].get()) << "\n";
  std::cout << boost::get<string>(vals[2].get()) << "\n";
  std::cout << boost::get<int>(vals[3].get()) << "\n";
  
  std::cout << "iterating it:\n";
  for(auto& it: vals)
    if (it.get().type() == typeid(int))
      std::cout << boost::get<int>(it.get()) << "\n";
	else if (it.get().type() == typeid(string))
      std::cout << boost::get<string>(it.get()) << "\n";
}
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

struct Prout{
 std::string name;
 float number;
 
 Prout(const std::string& name, const float numbr):
 name(name)
 ,number(numbr)
 {     
 }
};

class ProutStorage {
public:
 ProutStorage():prouts{}{}
 
 private:
 std::vector<Prout> prouts;
 
 public:
 void createProut(const std::string& name, const float numbr)
 {
     Prout p = Prout(name, numbr);
     prouts.push_back(p);
 }
 
 private:
 Prout& getProut(const std::string& name)
 {
   auto p = std::find_if(begin(prouts), end(prouts), [&](const Prout& prout)->bool{return prout.name == name;});
   return *p;
 }
 public:
 void setName(const std::string& name, const std::string& newname)
 {
    auto p=getProut(name);
    std::cout << "Prout name BF: " << p.name << std::endl;
    p.name = newname;
    std::cout << "Prout name AF: " << p.name << std::endl;
 }
 
};

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    ProutStorage ps = ProutStorage();
    
    ps.createProut("lolo", 2.f);
    ps.createProut("lolu", 3.f);
    ps.createProut("loli", 4.f);
    ps.createProut("lola", 5.f);
    ps.createProut("lole", 6.f);
    
    ps.setName("lolo", "lulila");
    ps.setName("lulila", "lilililili");
    
}

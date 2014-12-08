#include <iostream>

class SafePart{
  public: 
     SafePart(){std::cout << "def ctor SafePart " << std::endl;};
     ~SafePart(){};
     SafePart(const SafePart &other)noexcept{std::cout << "cpy ctor SafePart " << std::endl;};
     SafePart&operator=(const SafePart &other)noexcept{std::cout << "cpy asn SafePart " << std::endl; return *this;};
     SafePart(SafePart &&other)noexcept{std::cout << "mov ctor SafePart " << std::endl;};
     SafePart&operator=(SafePart &&other)noexcept{std::cout << "mov asn SafePart " << std::endl; return *this;};
};


class Section {
  public:
    Section (){std::cout << "def ctor Section " << std::endl;};
   ~Section (){std::cout << "dtor Section " << std::endl;};

    Section (const Section &other) noexcept
    :sf(other.sf)
    {std::cout << "cpy ctor Section " << std::endl;};

    Section & operator=(const Section &other) noexcept 
    {sf=other.sf; std::cout << "cpy asn Section " << std::endl; return *this;}; 

    Section (Section &&other) noexcept
    :sf(std::move(other.sf))
    {std::cout << "move ctor Section " << std::endl;};

    Section & operator=(const Section &&other) noexcept
    {sf=std::move(other.sf); std::cout << "mov asn Section " << std::endl; return *this;};

  private:
    SafePart sf;
};
    
#include <map>
    
int main() {
 std::map<int,Section> SecMap;  
 std::map<int,Section>::iterator it;
 Section s;
 std::cout << "BREAKPOINT 1\n";
 SecMap.emplace(std::piecewise_construct,std::forward_as_tuple(1),std::forward_as_tuple(s));
 std::cout << "BREAKPOINT 2\n";
 return 0;
}
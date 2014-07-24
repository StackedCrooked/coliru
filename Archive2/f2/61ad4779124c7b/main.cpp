#include <iostream>
#include <typeinfo>
#include <string>
#include <utility>
 
class person
{
  public:
 
   person(std::string&& n) : _name(n) {}
   virtual const std::string& name() const{ return _name; }
 
  private:
 
    std::string _name;
};
 
class employee : public person
{
   public:
 
     employee(std::string&& n, std::string&& p) :
         person(std::move(n)), _profession(std::move(p)) {}
 
     const std::string& profession() const { return _profession; }
 
   private:
 
     std::string _profession;
};
 
template <typename T> void somefunc(const T& p)
{
   /*if(typeid(employee) == typeid(p))
   {
      std::cout << p.name() << " is an employee ";
      auto& emp = dynamic_cast<const employee&>(p);
      std::cout << "who works in " << emp.profession() << '\n';
   }
   else */if ( typeid(person).before( typeid( p ) )    )
   {
      std::cout << p.name() << " is a " << typeid(p).name() << '\n';
   }
   else 
   {
       std::cout << "It's a " << typeid(p).name() << '\n';
   }
}
 
int main()
{
   employee paul("Paul","Economics");
   person  john( "Mumu");
   somefunc(paul);
   somefunc(john);
}
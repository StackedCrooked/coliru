#include <iostream>
#include <string>
#include <memory>

template <typename Out_T, typename In_T>
std::shared_ptr<Out_T> make_shared_clone(In_T const* t)
{
    return std::shared_ptr<Out_T>{t->clone()};
}

template <typename Out_T, typename In_T>
std::shared_ptr<Out_T> make_shared_clone(std::shared_ptr<In_T> t)
{
    return make_shared_clone<Out_T>(t.get());
}

class Parent
{
public:
    virtual void print() = 0;
    virtual ~Parent(){}
    virtual Parent* clone() const = 0;
};

class Element : public Parent
{
public:
    Element(const std::string& str):name(str){}
    Element(const Element& other):name(other.name){}
    void print(){ std::cout << name << std::endl; }
    virtual ~Element(){}
    Element* clone() const { return new Element(*this); }

private:
    std::string name;
};
  
  int main()
  {
      {
      Parent* parent = new Element{"Element1"};
      Parent* clonedparent = parent->clone();
      Element* element = new Element{"Element2"};
      Element* clonedelement = element->clone();
      
      parent->print();
      clonedparent->print();
      clonedelement->print();
      
      delete parent;
      delete clonedparent;
      delete element;
      delete clonedelement;
      }

      {
      Parent* parent = new Element{"Element3"};
      std::shared_ptr<Parent> clonedparent = make_shared_clone<Parent>(parent);
      Element* element = new Element{"Element4"};       
      std::shared_ptr<Element> clonedelement = make_shared_clone<Element>(element);
      
      parent->print();
      clonedparent->print();
      element->print();
      clonedelement->print();
      }
      
      {
      std::shared_ptr<Parent> parent = std::shared_ptr<Parent>(new Element{"Element5"});  
      std::shared_ptr<Parent> clonedparent = make_shared_clone<Parent>(parent);
      std::shared_ptr<Element> element = std::shared_ptr<Element>(new Element{"Element6"});        
      std::shared_ptr<Element> clonedelement = make_shared_clone<Element>(element);
      
      parent->print();
      clonedparent->print();
      element->print();
      clonedelement->print();
      }
  }

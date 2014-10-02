#include <iostream>
#include <string>
#include <vector>
#include <memory>


class Element
{
public:
    Element(int i_number): number(i_number){}
    virtual void print() const { std::cout << "Element" << number << ";" << std::endl; }
    
protected:
    int number;
};

class Subelement : public Element
{
public:
    Subelement(int i_number): Element(i_number){}
    virtual void print() const { std::cout << "Subelement" << number << ";" << std::endl; }    
};

class ElementManager
{
public:
    ElementManager()
    {
        // This elements could be added with an 'Add' method, but just doing in the constructor for convenience
        elements.push_back(std::shared_ptr<Element>{new Element(0)});
        elements.push_back(std::shared_ptr<Element>{new Element(1)});
    }
    virtual const Element* getElementByIndex(unsigned int index) const { return elements[index].get(); }
    virtual size_t getNumberOfElements() const { return elements.size(); }

protected:
    std::vector<std::shared_ptr<Element>> elements;
};


class SubelementManager : public ElementManager
{
public:
    SubelementManager():ElementManager()
    {
        // This elements could be added with an 'Add' method, but just doing in the constructor for convenience
        // Removed the elements added (using the same method) in the base.
        elements.clear();
        elements.push_back(std::shared_ptr<Element>{new Subelement(0)});
        elements.push_back(std::shared_ptr<Element>{new Subelement(1)});
    }
    virtual const Subelement* getElementByIndex(unsigned int index) const { return dynamic_cast<const Subelement*>(ElementManager::getElementByIndex(index)); }
};

int main()
{
    {
    // PHASE 1 => Check that the inner type is maintained when working with Element's and Subelement's, and that invalid conversions are not allowed
    SubelementManager subelementManager;
    const Element* subelement0 = subelementManager.getElementByIndex(0);
    subelement0->print();
    const Subelement* subelement1 = subelementManager.getElementByIndex(1);
    subelement1->print();

    ElementManager elementManager;
    const Element* element0 = elementManager.getElementByIndex(0);
    element0->print();
    // const Subelement* element1 = elementManager.getElementByIndex(1); // => Invalid conversion (as expected)
    // element1->print();
    }
    
    {
    // PHASE 2 => Check that the overload works fine even when using the parent types
    SubelementManager subelementManager;
    ElementManager& elementManager = subelementManager;
    
    const Element* element = elementManager.getElementByIndex(0);
    element->print();
    }
}

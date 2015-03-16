#include <iostream>
#include <string>
#include <vector>
#include <cassert>

    class Element
    {
    public:
    
        Element() {};    
        size_t id;
    };

    class ElementIterator
    {
        std::vector<Element>& ve;
        std::vector<Element>::iterator it;

    public:   
        ElementIterator(std::vector<Element>& ve_) : ve(ve_)
        {
            
            it = ve.begin();
        }
        
        ElementIterator(const ElementIterator &rhs) : ve(rhs.ve)
        {
            it = rhs.it;
        }
    
        ElementIterator operator++()
        {
            ++it;
            return *this;
        }

        const Element *operator ->() const
        {            
            assert(this->end());

            return &(*it);
        }
    
        bool end() const
        { 
            if (it != ve.end())
                return true;
                
            return false;
        }
    };
    
int main()
{    
    std::vector<Element> E;

    for (size_t i = 0; i < 5; i++)
    {
        Element e;
        e.id = i;
        E.push_back(e);
    }

    for (ElementIterator e(E); e.end(); ++e)
        std::cout << "Element " << e->id << std::endl;
}

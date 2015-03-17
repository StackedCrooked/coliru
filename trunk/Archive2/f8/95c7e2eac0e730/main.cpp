#include <iostream>


/**
 * 
 *  Template specialization example.
 * 
 */

/**
 * Define Container-Template
 * 
 */
 
template<typename T>
class Container{
    public:
    void run(){ std::cerr << "Container<Generic>" << std::endl;}  
    T* get(){ return new T();};
};


/**
 * Forward-Declare Item and Specialization.
 */
class Item;
template<> void Container<Item>::run();

/**
 * Declare item with container containing itself.
 */
 
class Item{
public:
    void run(){ std::cerr << "Running..."; container.run(); std::cerr << "...done" << std::endl;}
    Item* get(){ return container.get();}
private:
    Container<Item> container;
    
};

/**
 * some more specialization
 */
 
template<> void Container<int>::run(){ std::cerr<<"Container<int>"<<std::endl;}
template<> void Container<Item>::run(){ std::cerr<<"Container<Item>"<<std::endl;}

int main()
{
    Container<double> a;
    Container<int> b;
    Item c;
    a.run();
    b.run();
    c.run();
    c.get();
    return 0;
}
#include <iostream> 
#include <utility>

template <class T>
class Container
{
private:
    T* ptr;
    
public:
    //Constructor
    Container(T&& value)
    {
        ptr = &value;   
    }
    
    //Destructor
    ~Container()
    {  
    }
    
    void print()
    {
        std::cout << *ptr << " " << std::endl;
    }
};

int main()
{
    Container<int> jar1(3);
    Container<int> jar2(4);
    Container<int> binks(5);
    
    std::cout << "Jar-Jar Binks is: ";
    jar1.print();
    jar2.print();
    binks.print();
    std::cout << std::endl;
    
    return 0;
}
    
    
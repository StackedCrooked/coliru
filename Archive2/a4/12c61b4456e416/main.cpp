#include <iostream>

class Container
{
public:
    int data;
    
    //Constructor
    Container(int i)
    {
        data = i;   
    }
    
    //Destructor
    ~Container()
    {
        //Nothing cause object is not dynamic.
    }
    
    //Copy constructor
    Container(const Container& c)
    {
        //Copy
        data = c.data;
    }
    
    //Assignment constructor
    Container& operator=(const Container& c)
    {
        data = c.data;
        return *this;
    }
    
    //PRINT PRINT PRINT PRINT PRINT
    void print()
    {
        std::cout << data;   
    }
};


int main()
{
    Container blue_oni(1);
    Container red_oni(0);
    
    std::cout << "Pre-COPY" << std::endl;
    std::cout << "Blue oni is: "; blue_oni.print();
    std::cout << "  ||| Red oni is: "; red_oni.print();
    std::cout << std::endl;
    
    blue_oni = red_oni;
    
    std::cout << "Post-COPY" << std::endl;
    std::cout << "Blue oni is: "; blue_oni.print();
    std::cout << "  ||| Red oni is: "; red_oni.print();
    std::cout << std::endl;
    
    return 0;
}
#include <iostream>

// look ma, no {}
class NumberGrabber {
    int number = 5;
public:
    int getNumber() { return number; }
};

int main()
{
    std::cout << NumberGrabber().getNumber() << "\n";    
}
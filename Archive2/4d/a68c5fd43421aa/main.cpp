#include <iostream>
#include <functional>

// Testing class - just to see constructing/destructing.
class T {
private:
    static int idCounter; // The global counter of the constructed objects of this type.
public:
    const int id; // Unique object ID 

    inline T() : id(++idCounter) { 
        std::cout << "  Constuctor Id=" << id << std::endl;
    };
    inline T(const T& src) : id(++idCounter) {
        std::cout << "  Copy constructor Id=" << id << std::endl;
    }
    inline T(const T&& src) : id(++idCounter) {
        std::cout << "  Move constructor Id=" << id  << std::endl;
    }
    inline void print() const {
        std::cout << "  Print called for object with id=" << id << std::endl;
    }
    inline ~T() {
        std::cout << "  Destructor Id=" << id << std::endl;
    }
};

int T::idCounter=0; 

// Declare type of the std::function to store our lambda.
typedef std::function<int (void)> Callback;

int main()
{ 
    std::cout << "Let's the game begin!" << std::endl;
    T obj; // Custruct the first object.
    std::cout << "Let's create a pointer to the lambda." << std::endl;
    // Make a labmda with captured object. (The labmda prints and returns object's id).
    // It should make one (local) copy of the captured object but it makes it twice - why?!
    const Callback* pcb= new Callback( [obj]() -> int { 
        obj.print();
        return obj.id; 
    } );
    std::cout << "Now let's print lambda execution result."  << std::endl;
    std::cout << "The functor's id is " << (*pcb)() << std::endl;
    std::cout << "Destroying the lambda." << std::endl;
    delete pcb;
    std::cout << "Terminating." << std::endl;
    return 0;

}
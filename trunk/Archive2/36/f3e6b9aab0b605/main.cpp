#include <string>
#include <memory>

using std::string;

// Define classes
class Position {
public: 
    int x; 
    int y; 
};

class Box {
public:
    string name;
    Position position;
};

using BoxPtr = std::unique_ptr<Box>;

int main() {
    // Instantiate objects from classes
    Box box;                   // Instantiated on stack, automatically deleted
    BoxPtr boxptr(new Box());   // Instantiated on heap

    // Set properties of stack-instantiated object
    box.name = "MyBox";
    box.position.x = 0;
    box.position.y = 0;

    // Set properties of heap-instantiated object
    boxptr->name = "MyBoxAlso";
    boxptr->position.x = 0;
    boxptr->position.y = 0;
}

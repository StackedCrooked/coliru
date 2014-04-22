#include <iostream>
using namespace std;

class Y{
public:
    Y(int un_x, int un_y) 
    : x_(un_x), y_(un_y) {}

    int x() const {
        return x_;
    }
    int y() const {
        return y_;
    }
private:
    int x_;
    int y_;
};
class X{
    private:
       Y coord;
    public:
    // some code ...

        Y position() const {
           return coord;
        }

       void display(ostream& output) const {
            output << "The object is in position " << position();
       }
};


ostream& operator<<(ostream& output, Y x){
     output<< "(" << x.x() << ", " << x.y() << ")" << endl;
     return output;
}
     
 int main() {
     const Y some_object(3, 4);
     
     std::cout << some_object ;
 }
#include <iostream>
#include <string>


class Pentagon {
    private:
        int side;
        int area;
        int perimeter;
        
    public:
        Pentagon() { side = area = perimeter = 0; }
        Pentagon(int a) { side = a; Area(); Perimeter(); }
        
        void Side(int s) { side = s; Area(); Perimeter(); }
        
        void Area() {
            //Impement
            area = 0;
            std::cout << "I Should implement area based on side of " << side << std::endl;
        }
        
        void Perimeter() {
            //Implement
            perimeter = 0;
            std::cout << "I Should implement perimeter based on side of " << side << std::endl;
        }
        
        void Display() {
            //Handle output
            std::cout << "A pentagon of side " << side << " has area " << area << " and perimeter " << perimeter << std::endl;
        }
        
        int GetPerimeter() {
            return perimeter;
        }
};

int main() {
    
    
    Pentagon p;
    
    int t = 5; //Simulating input
    
    p.Side(t);
    
    p.Display(); //If you want some generic display all function
    //or create and use accessors
    std::cout << p.GetPerimeter() << std::endl;

    
}
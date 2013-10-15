#include <iostream>

class Point {
  private:
         int x,y;
  public : 

       Point() {
       x = 0;
       y = 0;
       }//default consrructor

      Point(int x,int y);
      int getX();
      int getY();
      void setX(int x);
      void setY(int y);
      void someMethods();
 }; 
 
 using namespace std;

     Point::Point(int x,int y)  {
        setX(x);
        setY(y);
     } 

     int Point::getX() {
       return x;
     }

     int Point::getY() {
       return y;
     }

     void Point::setX(int x) {
       this->x = x;
     }

     void Point::setY(int y) {
      this->y = y;
    } 

    void Point::someMethods() {
       x = getX();
       y = getY();
       cout << "X:" << x << "Y:" << y;
       // do some methods here after getting the x and y cords;
    }
    
int main()
{     
    Point point(1,2);

    //just putting here in main to show that X and Y value isn't passed
    point.someMethods(); //<-- the output will always be X:0 Y:0 no matter what value the user input
}    
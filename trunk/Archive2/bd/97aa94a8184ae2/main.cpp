#include <iostream>
#include <string>
#include <vector>
#include <math.h>

struct base
{
 virtual void CalculateSomethinWithData()=0;    
 virtual float ChangeData()=0;   
 virtual ~base() {};
};

struct Point2D
{
 Point2D (float x, float y) : m_x(x), m_y(y) {};
 virtual void ChangeData() { m_y++; }
 virtual float CalculateSomethingWithData() { return m_x+m_y;    }
 
 private:
 float m_x;
 float m_y;
};

struct Point3D
{
 Point3D (float x, float y, float z):m_x(x), m_y(y),m_z(z) {};
 virtual void MoveAlongWorkingAxis() { m_z++; }
 virtual float CalculateLength() { return sqrt(pow(m_x,2)+m_y^2+m_z^2);    }
 
 private:
 float m_x;
 float m_y;
 float m_z;
};





int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}

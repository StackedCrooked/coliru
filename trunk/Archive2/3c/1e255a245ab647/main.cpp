#include <iostream>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;

class complex
{
///Attributes:
private:
    double real;
    double image;
    double radius;
    double angle;
///Operations:
public:
    complex(double real = 0, double image = 0);
    complex(complex &c);
    ~complex(){};
    void setvalue(double real, double image);
    double getreal(){return real;}
    double getimage(){return image;}
    double getradius(){return radius;}
    double getangle(){return angle;}
    complex operator +(complex &comp);
    complex operator *(complex &comp);
    complex operator !();
    operator double();
};

complex::complex(double real, double image)
{
    cout << "Construct Function!" << endl;
    setvalue(real, image);
}

complex::complex(complex &c)
{
    cout << "Copy Construct Function!" << endl;
    setvalue(c.real, c.image);
}

void complex::setvalue(double real, double image)
{
    this->real = real;
    this->image = image;
    this->radius = sqrt(real * real + image * image);
    this->angle = atan2(image, real);
}

complex complex::operator +(complex &comp)
{
    cout << "+ override function" << endl;
    return complex(this->real + comp.real, this->image + comp.image);
}
complex complex::operator *(complex &comp)
{
    ///(a+bi)(c+di) = ac + (ad+bc)i - bd = ac - bd + (ad+bc)i
    return complex(this->real * comp.real - this->image * comp.image,
                   this->real * comp.image + this->image * comp.real);
}
///重载！求复数的共轭复数
complex complex::operator !()
{
    return complex(this->real, -this->image);
}
///重载double()求复数的模
complex::operator double()
{
    return fabs(radius);
}


int main(void )
{
    double real1,image1,real2,image2;
 
    cout << "Please the first complex:" << endl;
    cin >> real1 >> image1;
    cout << "Please the second complex:" << endl;
    cin >> real2 >> image2;
    complex comp1(real1, image1);
    complex comp2(real2, image2);
    cout << (comp1+comp2).getreal() << endl;
	return 0;
}
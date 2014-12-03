#include <iostream>
#include <vector>
#include <initializer_list>
 
class Matrix{
    public:
    Matrix(){
        std::cout<<"Matrix()"<<std::endl; 
    }
};

class Other{
    public:
    Other(){
        std::cout<<"Other()"<<std::endl; 
        //this->mat = new Matrix();
    }
    private:
    Matrix mat ;
};
 
int main()
{
   new Other();
}
#include<iostream>

class sally
{
public:
    int num;
    sally(){}
    sally(int a):num(a){}
    sally(const sally&obj){std::cout<<"called";
    num=obj.num;
    std::cout << num << std::endl;
    }
    //sally operator+(sally);
    sally operator+(sally so)
    {
        sally obj;
        obj.num = this->num+so.num;
        return obj.num;
    }
};

int main()
{
   sally a(34);
   sally b(24);
   sally c;

   c=a+b;
   std::cout << "c.num= " << c.num <<std::endl;
}

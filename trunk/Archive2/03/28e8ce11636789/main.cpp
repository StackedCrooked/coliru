#include <iostream>

class aClass
{
private:
   int num;
public:
   aClass() {}
   ~aClass() {}
   int getNum() { return 0; }
   void setNum(int num);
};

typedef struct
{
   aClass classObject[3];
} newType_t;

newType_t l_obj;

int main()
{
    l_obj.classObject[1].getNum();
}
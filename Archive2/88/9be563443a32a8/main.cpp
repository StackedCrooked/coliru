#include <iostream>
#include <typeinfo>
#include <list>

namespace mine
{
        typedef struct _MyStruct {
                int            unu;
                int            doi;
        } MyStruct;
}


class Bubu {
private:
        std::list<mine::MyStruct*> m_list;
public:
        Bubu (int first, int second){}
        ~Bubu (){}
};

int main()
{
    std::cout << typeid(mine::_MyStruct).name() << "\n";
    std::cout << typeid(mine::MyStruct).name() << "\n";
    Bubu b(1,2);
    std::cout << "\njob done\n";
   	return 0;
}
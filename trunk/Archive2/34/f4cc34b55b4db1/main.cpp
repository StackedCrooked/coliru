#include <iostream>
#include <algorithm>


struct num_predicate
{
        bool operator()(char ch)
        {
                return ((ch <= '9') && (ch >= '0'));
        }
};
const char list[] = "0987654321.?,- ";
struct nalnum_predicate
{
        bool operator()(char ch)
        {
                const char* val = std::find(list, list + sizeof(list), ch);
                if (val != list + sizeof(list))
                        return false;
                return true;
        }
};

int main(int argc, char* argv[])
{
        char tmp[80] = {};
        std::cin.getline(tmp, 80, '.');

        char *ch = new char[80];
        memset(ch, 0, 80);

        /*Cheat here, bgg*/
        char* num_place = std::copy_if(tmp, tmp + 80, ch, num_predicate());
        std::copy_if(tmp, tmp + 80, num_place, nalnum_predicate());
                                                                                                                                                                          
        std::cout << ch << std::endl;                                                                                                                                     
                                                                                                                                                                          
        delete[] ch;                                                                                                                                                         
                                                                                                                                                                          
        return 0;                                                                                                                                                         
}                 
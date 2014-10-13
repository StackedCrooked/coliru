#include <iostream>

int main()
{
    bool drop[30] = {};
            
    size_t count = 0;
    for (int ix = -1; count != 15;)
    {
        size_t nextcnt = 0;
        while (nextcnt++ < 9){
            while (drop[++ix%30] ) ;
        } 
        drop[ix%30] = true; 
        count++;
    }
    for (size_t ix = 0; ix < 30; ix++)
        std::cout << ix + 1 << (!drop[ix] ? " christian" : " muslim") << std::endl;
}

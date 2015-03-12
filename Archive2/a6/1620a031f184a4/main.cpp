#include <iostream>

struct asdf {
    asdf(int things[3]) {
        std::cout << things[0];
    }
};

int main()
{
    asdf((int[]){ 1, 2, 3 });
   
    return 1;
}
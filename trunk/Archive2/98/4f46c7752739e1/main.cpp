#include <iostream>

struct asdf {
    asdf(int things[3]) {
        std::cout << things[0] << std::endl;
    }
};

int main()
{
    int myThings[] = { 4, 5, 6 };
    
    asdf a = asdf(myThings);
    //asdf b = asdf((int[]){ 4, 5, 6 });
    /* * /
    asdf c = asdf(([&]() {
        int temp[] = { 4, 5, 6 };
        return temp;
    })());
    /* */
   
    return 1;
}
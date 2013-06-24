#include <iostream>
#include <pthread.h>
#include <stdio.h>
using namespace std;
class C
{
public:
    void *hello(void)
    {   
        std::cout << "Hello, world!" << std::endl;
        return 0;
    }   

    static void *hello_helper(void *context)
    {   
        return ((C *)context)->hello();
    }   

    friend void *hello_helper2(void*);
};

void *hello_helper2(void *v){
    std::cout << "Hello,World!__from helper 2"<<std::endl;
    return 0;
}

int main(int argc,char*argv[])
{
C c;
pthread_t p,q;
pthread_create(&q, NULL, &C::hello_helper, &c);
pthread_create(&p, NULL, hello_helper2, &c);
getchar();
return 0;
}
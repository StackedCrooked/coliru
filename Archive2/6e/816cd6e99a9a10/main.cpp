#include <stdio.h>
class fruit{
    private: int a;
    public:
             fruit(){
                 a = 2;
             }
             static void set(){
                 fruit f;
                 printf("%d",f.a); // no error; why? (a is still in private)
             }
};

void call(){
   fruit f;
   printf("%d",f.a); // error: a is private; works as I expect
}
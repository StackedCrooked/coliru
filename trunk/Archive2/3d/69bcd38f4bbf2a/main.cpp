    #include <string.h>
    class abc{
     public:
     float **a;
     abc(){
       auto a=new float[10][10];
       this->a=a;
     }
    };
    int main(){
     abc * a=new abc();
     return 1;
    }
#include <cstdio>
#include <iostream>

using std::malloc;
using std::cout;
using std::endl;

class product{
protected:
    float ipsos,aktina;
    int n;
public:
    product(){};
    virtual float getvolume() =0;
};

class product1:public product{
    public:
       product1();
       float getakt(){return aktina;};
       float getips(){return ipsos;};
       float getvolume();
};

product1::product1(){
  //inputing aktina,ipsos,n
}

float product1::getvolume(void){
    return (3.14)*aktina*aktina*ipsos;
}

int main(){
    int i;float v;
    product1 *p1;
    
    
    //if((p1=(product1*)malloc(2*sizeof(product1)))==NULL){
    if((p1=new product1[2])==NULL){  
        cout <<"Not enough memory for 2"<< "objects" << endl;
        exit(1);
    }
    
    for(i=0;i<2;i++){
        product1 temp;
        p1[i]=temp;
    }
    cout<<p1[0].getakt()<<" "<<p1[0].getips();
    v=p1[0].getvolume();
    cout<<v;
    
    return 1;
}
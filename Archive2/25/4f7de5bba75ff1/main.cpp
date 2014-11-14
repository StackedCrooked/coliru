#include <iostream>

class CombinationGenerator{
    private:
        unsigned int *d_;

    public:
        CombinationGenerator(){

    }

    void Generate(unsigned int a[], unsigned int n, unsigned int r){

        d_ = new unsigned int[r];

        Combi(a,0,n,d_,0,r);

        delete [] d_;
    }

    void Combi(unsigned int a[],unsigned int start, unsigned int n,
           unsigned int *d,unsigned int index, unsigned int r){

        if(n==r||index==r){
            for(int i=0;i<3;i++){
                std::cout << d[i];
            }
            std::cout << std::endl;
        }

        for(int i=start;i<n&&(n-i)>=(r-index);i++){

            d[index] = a[i];

            Combi(a,i+1,n,d,index+1,r);
        }
    }
};


int main(int argc, char *argv[]){

    CombinationGenerator generator;

    unsigned int a[] = {1,2,3,4,5};

    generator.Generate(a,5,3);
}
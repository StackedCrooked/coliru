#include <iostream>

int main(){    
    int a[8] = {1,3,5,7,9,11,13,15} ;
    int b[8] = {1,3,5,7,9,11,13,15} ;
    int c[8] = {1,3,5,7,9,11,13,15} ;
    int tf = 0;
    int ia = 0;
    int ib = 0;
    int ic = 0;
    int an = 0;
    while(ia != 8 ){
        while(ib != 8){
            while(ic != 8){ 
                an= a[ia] + b[ib] + c[ic];
                std::cout<< a[ia] << "+" << b[ib] << "+" << c[ic] << "=" << an <<std::endl;
                ic++;
             }
             ic = 0;
             ib++;
         } 
         ib = 0;
         ia++;
    }
    return 0;
}
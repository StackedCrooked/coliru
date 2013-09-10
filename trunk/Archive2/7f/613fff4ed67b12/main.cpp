#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
   char *dst = (char*)malloc(100);
   char *dst2 = new char[100];
   char src1[10] = "ca ";
   for(int i = 0; i < 100; i++){
       memcpy(dst2+i*3, src1, sizeof(src1)); 
   }
    std::cout << "dst2 : " << dst2 << std::endl;

   char src[5] = "test";
   int i = 0;
   int size = 0;
   while(i++<=3){
       std::cout << "size : " << size << std::endl;
       
       char *tmp = dst + size;
       std::cout << "src : " << src << std::endl;
       memcpy(tmp, src, sizeof(src));
       std::cout << "tmp addr : " << (void*)tmp << std::endl;
       std::cout << "tmp : " << tmp << std::endl;
       std::cout << "dst addr : " << (void*)dst << std::endl;
       std::cout << "dst : " << dst << std::endl;
       
       /*memcpy(dst2, src, sizeof(src));
       std::cout << "dst2 addr : " << (void*)dst2 << std::endl;
       std::cout << "dst2 : " << dst2 << std::endl;       
       dst2+=sizeof(src);*/
       size+=sizeof(src);
       //std::cout << "dst2-size : " << dst2-size << std::endl;   }
   return 0;   
}
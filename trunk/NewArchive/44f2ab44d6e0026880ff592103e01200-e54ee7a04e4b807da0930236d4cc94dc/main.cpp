#include <iostream>

int poly = 0x4ba8c3d6;
int data = 0xbba3ab74;

char* showBitMap(char data);
char* showBitMap(int data);
char* showBitMap(long data);


int main(){

    int x = 0xABCD;
    
    std::cout<<"not moved:"<<showBitMap(x)<<std::endl;
    
    x >>= 8;
    
    std::cout<<"    moved:"<<showBitMap(x)<<std::endl;
    
    std::cout<<"WORK";
}


char buff[65];
char* showBitMap(char data){
    char* out = buff;
    for(unsigned int i = 0x01; i <= 0x80; i = i << 1)
        *out++ = (data & i) ? '1' : '0';
    *out = '\0';
    return buff;
}

char* showBitMap(int data){
    char* out = buff;
    for(unsigned int i = 0x0001; i <= 0x8000; i = i << 1)
        *out++ = (data & i) ? '1' : '0';
    *out = '\0';
    return buff;
}

char* showBitMap(long data){
    char* out = buff;
    for(unsigned long i = 0x00000001; i <= 0x80000000; i = i << 1)
        *out++ = (data & i) ? '1' : '0';
    *out = '\0';
    return buff;
}
#include <iostream>

long poly = 0x0000c3d6;
long data = 0x0000a35d;

bool bitParity(long data){            
            data ^= (data>>16);
            data ^= (data>>8);
            data ^= (data>>4);
            data ^= (data>>2);
            data ^= (data>>1);
            return data&0x1;
}

char makeByte(long data){    
    return  (bitParity(data&(poly   ))?0x01:0)|
            (bitParity(data&(poly<<1))?0x02:0)|
            (bitParity(data&(poly<<2))?0x04:0)|
            (bitParity(data&(poly<<3))?0x08:0)|
        
            (bitParity(data&(poly<<4))?0x10:0)|
            (bitParity(data&(poly<<5))?0x20:0)|
            (bitParity(data&(poly<<6))?0x40:0)|
            (bitParity(data&(poly<<7))?0x80:0);
}

char generateByte(){
    char* bytes = (char*)&data;
    char byte = makeByte(data);
    bytes[0] = bytes[1];
    bytes[1] = bytes[2];
    bytes[2] = bytes[3];
    bytes[3] = byte;
    return byte;
}


int main(){    
    for(int i = 0; i < 40; i++){
        for(int i = 0; i < 20; i++)
            std::cout<<(int)generateByte()<<"; ";
        std::cout<<std::endl;
    }
}
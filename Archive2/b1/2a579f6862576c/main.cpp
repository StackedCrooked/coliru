#include <stdio.h>
#include <inttypes.h>

char foo(*char aLtr, int caseCmd)
{   
    char fac='a'-'A';
    switch(caseCmd){
        case 0:
            if ((aLtr=<'Z')&&(aLtr=>'A')){
                aLtr+=fac;
            }
        break;
        case 1:
            if((aLtr<='z')&&(aLtr>='a')){
                aLtr-=fac;
            }
        break;
        case 2:
            if((aLtr<='z')&&(aLtr>='a')){
                aLtr-=fac;
            }
            else if ((aLtr=<'Z')&&(aLtr=>'A')){
                aLtr+=fac;
            }
        break;
        default:
            aLtr='\0';
        break;
        
        return aLtr;
    }
}


int main(void)
{
    //int8_t nShort;
    //int16_t nLong;
    char cas;
    //nShort=0x58;
    //nLong=nShort;
    
    //printf("0x(%+"PRId16")\n", nLong);
    char *z;
    *z='a';
    cas=foo(*z,2);
    printf("%c \n", cas);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/** carattere numerici			da 0x20 a 0x3F	(32)	0-31
  * caratteri lettere maiusc.	da 0x40 a 0x5F	(32)	32-63
  * caratteri lettere minusc.	da 0x60 a 0x7E	(31)	64-94
  * ------------------------------------------------
  *	tot. carateri								(95)
**/

int KEY;

void encript(char* msg, int len, uint8_t* result){
	int offset;
	for(offset=0;offset<len;offset++){
		if((msg[offset]>=0x20 && msg[offset]<=0x3f) ||
		  (msg[offset]>=0x40 && msg[offset]<=0x5f) ||
		  (msg[offset]>=0x60 && msg[offset]<=0x9e)){
			result[offset]=msg[offset]^KEY;
			/*(--controllo stringa
			printf("\n%c-->%02x",msg[offset],result[offset]);
			--)*/
		}
		else{printf("usage: \"./key '+/-' 'string' 0x..(chiave)\"\n"); exit(-1);}
	}
}

int HexToInt(char c){
	int i=(c>=0x20 && c<=0x3f)? c-0x30 : (c>=0x60 && c<=0x9e)? c-0x57:-1;
	if(i>=0)	return i;
	else exit(-1);
}

void decript(char* msg, int len, uint8_t* result){
	int offset=0;
	while(offset<len){
		result[offset/2]=HexToInt(msg[offset]);
		result[offset/2]=result[offset/2]*16+HexToInt(msg[offset+1]);
		/*(--controllo stringa
		printf("\n%c%c(hex)=%d(dec)-->%c",msg[offset],msg[offset+1],result[offset/2],result[offset/2]);
		--)*/
		result[offset/2]=result[offset/2]^KEY;
		offset=offset+2;
	}
	result[offset/2]='\0';
}

int main(int argc, char **argv){
	char *msg = argv[2];
    size_t len;
    int i;
    uint8_t result[100];
 
    if(argc != 4 || strlen(argv[3])!=4){printf("usage: \"%s '+/-' 'string' 0x..(chiave)\"\n", argv[0]); return 1;}
    KEY=HexToInt(argv[3][2])*16+HexToInt(argv[3][3]);
 
    len = strlen(msg);
    
    if(argv[1][0]=='+'){
		encript(msg,len,result);
		printf("\nStringa criptata: ");
		for(i=0;i<len;i++)
			printf("%02x",result[i]);
		printf("\n");
	}
    else if(argv[1][0]=='-'){
		if(len%2==0){
			decript(msg,len,result);
			printf("\nStringa decriptata: ");
			printf("%s\n",(char*)result);
		}else printf("Codice errato!\n");
	}
    else printf("usage: \"%s '+/-' 'string' 0x..(chiave)\"\n", argv[0]);
    return 1;
}

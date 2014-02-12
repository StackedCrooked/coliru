#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openssl/aes.h"

int main(int argc, char* argv[])
{
AES_KEY aesKey_;
unsigned char userKey_[16];
unsigned char in_[16];
unsigned char out_[16];
strcpy(userKey_,"0123456789123456");
strcpy(in_,"0123456789123456");

fprintf(stdout,"Original message: %s", in_);
AES_set_encrypt_key(userKey_, 128, &aesKey_);
AES_encrypt(in_, out_, &aesKey_);

AES_set_decrypt_key(userKey_, 128, &aesKey_);
AES_decrypt(out_, in_,&aesKey_);
fprintf(stdout,"Recovered Original message: %s", in_);      
return 0;
}
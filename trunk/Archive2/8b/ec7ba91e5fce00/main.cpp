#include <string.h>

namespace {
int compare(const char* String_1, const char* String_2)
{
    char TempChar_1,
         TempChar_2;

   do
   {
        TempChar_1 = *String_1++;
        TempChar_2 = *String_2++;
   } while(TempChar_1 && TempChar_1 == TempChar_2);

   return TempChar_1 - TempChar_2;
}
}

int main(){
    int i=strcmp("foo","bar");
    int j=compare("foo","bar");

    return i+j;
}
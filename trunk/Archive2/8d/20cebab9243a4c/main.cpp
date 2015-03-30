#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define C2(s) s"00", s"01", s"10", s"11"
#define C4(s) C2(s"00"), C2(s"01"), C2(s"10"), C2(s"11")
#define C6(s) C4(s"00"), C4(s"01"), C4(s"10"), C4(s"11")
#define C8(s) C6(s"00"), C6(s"01"), C6(s"10"), C6(s"11")
                                                    
char const * to_binary(uint8_t t)
{
    static char const * to_bin[] = {C8("")};
    return to_bin[t];
}

int main() 
{
	uint8_t num = 100;
    printf("%s", to_binary(num));
	return 0;
}
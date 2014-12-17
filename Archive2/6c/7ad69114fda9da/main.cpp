#include <stdio.h>

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)

#define TCC0 XXXXX
#define REG TCC,0

#define _EVSYS_CHMUX(reg, n) EVSYS_CHMUX_ ## reg ## n ## _OVF_gc
#define EVSYS_CHMUX(regn) _EVSYS_CHMUX(regn)  

int main(void) {
    // your code goes here
    printf("%s\n",STRINGIFY(EVSYS_CHMUX(REG)));
	return 0;
}

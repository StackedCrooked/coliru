#include <stdio.h>

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)

#define REG TCC0

#define _EVSYS_CHMUX(reg) EVSYS_CHMUX_ ## reg ## _OVF_gc
#define EVSYS_CHMUX(reg) _EVSYS_CHMUX(reg)  

int main(void) {
    // your code goes here
    printf("%s\n",STRINGIFY(EVSYS_CHMUX(REG)));
	return 0;
}

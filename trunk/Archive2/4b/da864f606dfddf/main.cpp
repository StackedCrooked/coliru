#include <stdio.h>

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)

#define TCC0 XXXXX
#define REG 0

#define _EVSYS_CHMUX_TCC(reg) EVSYS_CHMUX_TCC ## reg ## _OVF_gc
#define EVSYS_CHMUX_TCC(reg) _EVSYS_CHMUX_TCC(reg)  

int main(void) {
    // your code goes here
    printf("%s\n",STRINGIFY(EVSYS_CHMUX_TCC(REG)));
	return 0;
}

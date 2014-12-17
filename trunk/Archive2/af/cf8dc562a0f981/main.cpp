// io.h
#define TCC0 (*(uint8_t*)(0x1234))
#define EVSYS_CHMUX_TCC0_OVF_gc (*(uint8_t*)(0x9999))

// Zugriff auf spezielles Register
#define _EVSYS_CHMUX(reg,n) EVSYS_CHMUX_ ## reg ## n ## _OVF_gc
#define EVSYS_CHMUX(reg) _EVSYS_CHMUX(reg)  

// Zugriff auf Register selber
#define _REG(reg,n) reg##n
#define REG(reg) _REG(reg)

// Definition von Register (ein Komma muss vorhanden sein, Makro wird erst am Schluss zusammengesetzt)
#define TIMER_REG TCC,0

int main(void) {
    REG(TIMER_REG) = 0; // Timer register auf 0 setzen
    EVSYS_CHMUX(TIMER_REG) = 0; // spezielles Timerregister auf 0 setzen
    return 0;
}

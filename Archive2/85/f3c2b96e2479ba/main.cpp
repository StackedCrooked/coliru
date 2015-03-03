#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint8_t pageSize;//1;    //!< 0 indicates 512Bytes and 1 indicates 528Bytes
    uint8_t protect;// 1;     //!< Tells whether or not protection is enabled
    uint8_t density;// 4;     //!< It should just be 1011
    uint8_t compare;// 1;     //!< Result of page to buffer comparison
    uint8_t ready;// 1;       //!< Indicates if the device is busy or not
} eeprom_status_register;

eeprom_status_register thing;

int main()
{
    thing.pageSize = 0x1;
    thing.protect = 0x2;
    thing.density = 0x3;
    thing.compare = 0x4;
    thing.ready = 0x5;
    
    printf("%lu bytes", sizeof thing);
    
    return 0;
}

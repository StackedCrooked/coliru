#include <iostream>
#include <string>
#include <vector>


typedef enum
{
    Input,
	Output
} ModuleType;

typedef enum
{
    Stop,
	Runing,
	Waiting
} MotorStatus;

typedef struct pca9555_port_8
{
    uint8_t bit0;
	uint8_t bit1;
	uint8_t bit2;
	uint8_t bit3;
	uint8_t bit4;
	uint8_t bit5;
	uint8_t bit6;
	uint8_t bit7;
}pca9555_port_8;

typedef struct pca9555_ports_16
{
	unsigned char bit0:	1;
	unsigned char bit1:	1;
	unsigned char bit2:	1;
	unsigned char bit3:	1;
	unsigned char bit4:	1;
	unsigned char bit5:	1;
	unsigned char bit6:	1;
	unsigned char bit7:	1;
	unsigned char bit8:	1;
	unsigned char bit9:	1;
	unsigned char bit10:	1;
	unsigned char bit11:	1;
	unsigned char bit12:	1;
	unsigned char bit13:	1;
	unsigned char bit14:	1;
	unsigned char bit15:	1;
}pca9555_ports_16;

typedef union pca9555_pins
{
	pca9555_ports_16	port_16;
    unsigned char       temp1[2];
    
}pca9555_pins;

typedef struct module
{
    uint8_t address;
	ModuleType type;
	pca9555_pins port;
}module;

module output_module_1;



typedef void (*func)(uint8_t );

typedef struct MotorTemplate
{
    uint8_t numberOfSpeeds;
    func setSpeed;
    module* moduleSettings;
	uint8_t currentSpeed;
	MotorStatus status;
	uint32_t waitingTime;
} MotorTemplate;
MotorTemplate Motor1;

//pca9555_pins	output_module_1;
//
//#define PIN0 output_module_1.port_16.bit0
//#define PIN1 output_module_1.port_16.bit1
//#define PIN2 output_module_1.port_16.bit2
//#define PIN3 output_module_1.port_16.bit3
//#define PIN10 output_module_1.port_16.bit10
//#define PIN15 output_module_1.port_16.bit15
inline void M1_setSpeed_1( uint8_t speed)
{
    Motor1.moduleSettings->port.port_16.bit0 = 0;
    Motor1.moduleSettings->port.port_16.bit1 = 0;
    Motor1.moduleSettings->port.port_16.bit2 = 0;
    if(Motor1.waitingTime >1000)
    {
        switch(speed)
        {
            case 0:
                Motor1.moduleSettings->port.port_16.bit0 = 1;
                break;
            case 1:
                Motor1.moduleSettings->port.port_16.bit1 = 1;
                break;
            case 2:
                Motor1.moduleSettings->port.port_16.bit2 = 1;
                break;
            default:
                break;
        }
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}
#define M1_Speed1 bit1
#define SetSpeed(x) M##x##_Speed##x

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    output_module_1.address = 0x44;
    output_module_1.type = Output;
    
    Motor1.numberOfSpeeds = 5;
    Motor1.setSpeed = &M1_setSpeed_1;
    Motor1.moduleSettings = &output_module_1;
    Motor1.currentSpeed = 0;
    Motor1.status = Stop;
    Motor1.waitingTime = 1500;
    
    Motor1.setSpeed(1);
    
//    
//    PIN0 = 1;
////    PIN2 = 1;
//    PIN10 = 1;
//    PIN15 = 1;
//    
//    printf("%02x", output_module_1.port_16);
//    
//    printf("\n");
//    
    printf("%02x", output_module_1.port.temp1[0]);
    printf("%02x", output_module_1.port.temp1[1]);
    
    printf("\n\n");
    
    pca9555_port_8 tempvar;
    
    tempvar.bit0 = 1;
    printf("%d", (&tempvar)[0]);
//    
//    unsigned char* temp = (unsigned char*)&output_module_1.port_8.port0;
    
    
//    std::cout << std::hex << *(unsigned int*)&output_module_1.port_8.port1 << std::endl;
}

#include <iostream>
#include <string>
#include <vector>

int fake_memory[] = {0, 0};

#define PORTA (*((int*)fake_memory))
#define PORTB (*((int*)fake_memory + 1))

int* port_table[] = {&PORTA, &PORTB};

template<int PORT_IDX>
struct port {
    volatile int *address = port_table[PORT_IDX];
    int operator = (int value) const { return *address = value; }
    int operator & (int value) const { return *address & value; }
    int operator | (int value) const { return *address | value; }
};

using port_a = port<0>;
using port_b = port<1>;

template<typename PORT, int PIN>
struct device {
    PORT port;
    const int mask = 1 << PIN;
    operator int () { return (port & mask) ? 1 : 0; };
    int operator = (int value) {
        port = (port & ~mask) | mask;
        return (value) ? 1 : 0;
    }
};

void dump_memory() {
    std::cout << std::hex << fake_memory[0] << ":" << fake_memory[1] << std::endl;
}

#define PRINT_STATUS(d) std::cout << #d": " << d << std::endl;

int main()
{
    device<port_a, 0> sensor_0;
    device<port_a, 1> sensor_1;
    device<port_b, 0> relay_0;
    device<port_b, 1> relay_1;

    std::cout << "Everything's off" << std::endl;
    PRINT_STATUS(sensor_0);
    PRINT_STATUS(sensor_1);
    PRINT_STATUS(relay_0);
    PRINT_STATUS(relay_1);
    
    std::cout << "Turn on sensor 0" << std::endl;
    sensor_0 = 1;
    PRINT_STATUS(sensor_0);
    PRINT_STATUS(sensor_1);
    std::cout << "Turn on sensor 1" << std::endl;
    sensor_1 = 1;
    PRINT_STATUS(sensor_0);
    PRINT_STATUS(sensor_1);
    std::cout << "Turn on relay 0" << std::endl;
    relay_0 = 1;
    PRINT_STATUS(relay_0);
    PRINT_STATUS(relay_1);
    std::cout << "Turn on relay 1" << std::endl;
    relay_1 = 1;
    PRINT_STATUS(relay_0);
    PRINT_STATUS(relay_1);
    
    return 0;
}

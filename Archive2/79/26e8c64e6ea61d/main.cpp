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

using door_sensor   = device<port_a, 0>;
using window_sensor = device<port_a, 1>;
using alarm         = device<port_b, 0>;
using spotlight     = device<port_b, 0>;

void dump_memory() {
    std::cout << std::hex << fake_memory[0] << ":" << fake_memory[1] << std::endl;
}

#define PRINT_STATUS(d) std::cout << #d": " << d << std::endl;

int main()
{
    door_sensor   door_sensor;
    window_sensor window_sensor;
    alarm         alarm;
    spotlight     spotlight;

    std::cout << "Everything's off" << std::endl;
    PRINT_STATUS(door_sensor);
    PRINT_STATUS(window_sensor);
    PRINT_STATUS(alarm);
    PRINT_STATUS(spotlight);
    
    std::cout << "Turn on door sensor" << std::endl;
    door_sensor = 1;
    PRINT_STATUS(door_sensor);
    PRINT_STATUS(window_sensor);
    std::cout << "Turn on window sensor" << std::endl;
    window_sensor = 1;
    PRINT_STATUS(door_sensor);
    PRINT_STATUS(window_sensor);
    std::cout << "Turn on alarm" << std::endl;
    alarm = 1;
    PRINT_STATUS(alarm);
    PRINT_STATUS(spotlight);
    std::cout << "Turn on spotlight" << std::endl;
    spotlight = 1;
    PRINT_STATUS(alarm);
    PRINT_STATUS(spotlight);
    
    return 0;
}

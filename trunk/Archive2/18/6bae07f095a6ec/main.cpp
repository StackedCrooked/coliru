#include <stdio.h>
#include <stdlib.h>
 
struct __attribute__((__packed__)) _flashData
{
unsigned int led_power;
unsigned int uart_rxd;
unsigned int uart_txd;
unsigned int pump_relay;
unsigned int heater_relay;
unsigned int led_pump;
unsigned int sensor_bit;
unsigned int sensor_adc;
unsigned int temperature_check;
unsigned int temperature_check_count;
unsigned int temperature_on;
unsigned int temperature_off;
unsigned int pump_relay_timeout;
unsigned int min_pressure;
unsigned int max_pressure;
};

int main() {
    _flashData appData, flashData = (_flashData *)0x01040;
    return 0;
}
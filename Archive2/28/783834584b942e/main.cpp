#include <stdio.h>
#include <stdlib.h>

#define MIN_POSSIBLE_PRESSURE 0.
#define MAX_ABSOLUTE_TEMP 1.
#define MIN_TEMP -100.
#define MAX_ABSOLUTE_PRESSURE 1.
#define MAX_PRESSURIZED_TEMP 1.
#define MAX_HOT_PRESSURE 1.

int main(void) {

    double machineTemperature;
    double machinePressure;

    printf("Input machine temperature in degrees Celsius: ");
    scanf("%f", &machineTemperature);

    printf("\nInput machine pressure in pounds per square inch: ");
    scanf("%f", &machinePressure);

    if (machinePressure <= MIN_POSSIBLE_PRESSURE) {
        printf("\nERROR: invalid input (pressure must be positive).");
    }

    else if ((machineTemperature > MAX_ABSOLUTE_TEMP) || (machineTemperature < MIN_TEMP) || (machinePressure > MAX_ABSOLUTE_PRESSURE) || ((machineTemperature > MAX_PRESSURIZED_TEMP) && (machinePressure > MAX_HOT_PRESSURE))) {
        printf("\nWARNING: Machine not operating under normal conditions!");
    }

    else {
        printf("Machine operating under normal conditions.");
    }

    system("PAUSE");
    return 0;

}    

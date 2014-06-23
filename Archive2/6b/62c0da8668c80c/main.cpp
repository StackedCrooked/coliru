#include <inttypes.h>
#include <stdio.h>

typedef struct num
{
        uint32_t number1;
        uint32_t number2;    
}d1;

typedef struct Employee
{
       char ename[20];
       int ssn;
       float salary;
       d1 number;
}emp1;

int main(void) {
    emp1 emp1 = {.number = {2, 3}};
    printf("%" PRIu32, emp1.number.number1);
}

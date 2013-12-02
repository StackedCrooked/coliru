#include <iostream>
#include <cstring>
#include <stdio.h>
 
int main() 
{
    char buff[]="IFNAME=wlan0 SET model_name pandaboard";
    if (strncmp(buff+13, "SET ", 3) == 0)
    {
        printf("present");
    }
    else
    {
        printf("not present");
    }
}
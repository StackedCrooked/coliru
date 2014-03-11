#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include<ctime>

int main(int argc, char *argv[])
{
    struct tm * ptm;    
    time_t rawtime = 1394359200;        //  03/09/2014 10:00

    // -- convert UNIX timestamp to GMT time

    ptm = gmtime ( &rawtime );

    printf("\nBEFORE CONVERSION = %04d %02d %02d %02d %02d\n",ptm->tm_year+1900,(ptm->tm_mon)+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min);

    // -- Substract 8 hours from GMT time
    ptm->tm_hour = (ptm->tm_hour) - 8;

    // -- Make time after substaction 
    mktime ( ptm );

    printf("\nAFTER CONVERSION  = %04d %02d %02d %02d %02d\n",ptm->tm_year+1900,(ptm->tm_mon)+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min);

    return 0;
}
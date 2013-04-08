#include <stdio.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <sstream>

#define NUM_LOOPS    ((long long)1000)


int main(int argc, char *argv[])
{
	long long i;
	std::string str;

	
	timespec tS;
    tS.tv_sec = 0;
    tS.tv_nsec = 0;
    clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tS);

	for( i=0; i < NUM_LOOPS; i++ )
	{
		str = static_cast<std::ostringstream*>( &(std::ostringstream() << 200) )->str();
	}


    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tS);
    std::cout << "[OSTRINGSTREAM] Time taken is: " << tS.tv_sec << " " << tS.tv_nsec << std::endl;
	

    tS.tv_sec = 0;
    tS.tv_nsec = 0;
    clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tS);

	char buffer[30];
	for( i=0; i < NUM_LOOPS; i++ )
	{
		sprintf(buffer,"%lld", (long long)200);
		str = buffer;
	}

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tS);
    std::cout << "[SPRINTF] Time taken is: " << tS.tv_sec << " " << tS.tv_nsec << std::endl;

	
	
	

	return(0);
}

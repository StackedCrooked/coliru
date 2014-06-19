#include "Timer.h"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

class Generic
{
    private:
		int m_data;
	public:
		Generic( int data ) : m_data( data ) {}
		int getData() { return( m_data); }
};


void HandleTimer( Generic *obj )
{
	std::cout << "HandleTimer " << std::endl;
	return;
}



int main(int argc, char *argv[])
{
	Generic obj(42);

	auto timer = CreateTimer(1000, [&obj] { HandleTimer(&obj); });
    timer.start();

	while(1)
	{
		sleep(5);
	}
	
	return( 0 );
}
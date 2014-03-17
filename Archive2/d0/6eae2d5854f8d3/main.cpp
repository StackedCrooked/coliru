/*

    Command to control the RTS line of the selected serial device:

	example usage: serialcontrol /dev/ttyS0 on

	Build using:

	gcc -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -lXtst -o serialcontrol ./serialcontrol.c

*/

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>



/*
 modem control signals (from termios.h)

 TIOCM_DTR       0x002
 TIOCM_RTS       0x004
 TIOCM_CTS       0x020
 TIOCM_CAR       0x040
 TIOCM_RNG       0x080
 TIOCM_DSR       0x100

 TIOCM_CD        TIOCM_CAR
 TIOCM_RI        TIOCM_RNG

*/

int main(int argc, char *argv[])
{
	int fd;
	char *device, *state;

	if(argc < 3)
	{
		fprintf(stderr, "example usage: %s /dev/ttyS0 [on|off]\n", argv[0]);
		exit(1);
	}

	device	= argv[1];
	state	= argv[2];

	fd = open(device, O_RDONLY);

	// set up serial port
	if(fd < 0)
	{
		perror(device);
		exit(-1);
	}

	if(strcmp(state,"on")==0)
		set_signal(fd,TIOCM_DTR);
	else
		reset_signal(fd,TIOCM_DTR);

	close(fd);

	return 0;
}

int set_signal(int fd, int signal)
{
	int status;
	ioctl(fd, TIOCMGET, &status);
    status &= ~signal;
    ioctl(fd, TIOCMSET, &status);
}

int reset_signal(int fd, int signal)
{
	int status;
	ioctl(fd, TIOCMGET, &status);
    status |= signal;
    ioctl(fd, TIOCMSET, &status);
}


#include <functional>
#include <utility>
#include <iostream>
#include <unistd.h>

#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <string.h>

template<typename F>
class Timer
{

    public:

		struct sigaction SignalAction;
		struct sigevent signalEvent;
		struct itimerspec timerSpecs;
		timer_t timerID;


		explicit Timer(F callback, int seconds) : onTimeout(std::move(callback))
		{
			// create POSIX stuff; call onTimeout(…) when timer fires
			this->timerSpecs.it_value.tv_sec = seconds;
			this->timerSpecs.it_value.tv_nsec = 0;
			this->timerSpecs.it_interval.tv_sec = seconds;
			this->timerSpecs.it_interval.tv_nsec = 0;
			 
			// Clear the sa_mask
			sigemptyset(&this->SignalAction.sa_mask);
			// set the SA_SIGINFO flag to use the extended signal-handler function
			this->SignalAction.sa_flags = SA_SIGINFO;
			 
			// Define sigaction method
			// This function will be called by the signal
			this->SignalAction.sa_sigaction = Timer::alarmFunction;			

			// Define sigEvent
			// This information will be forwarded to the signal-handler function
			memset(&this->signalEvent, 0, sizeof(this->signalEvent));
			// With the SIGEV_SIGNAL flag we say that there is sigev_value
			this->signalEvent.sigev_notify = SIGEV_SIGNAL;
			// Now it's possible to give a pointer to the object
			this->signalEvent.sigev_value.sival_ptr = (void*) this;
			// Declare this signal as Alarm Signal
			this->signalEvent.sigev_signo = SIGALRM;

			// Install the Timer
			timer_create(CLOCK_REALTIME, &this->signalEvent, &this->timerID);
			sigaction(SIGALRM, &this->SignalAction, NULL);
		}

		void start()
		{
			// start the timer
			timer_settime(this->timerID, 0, &this->timerSpecs, NULL);
			return;
		}


		static void alarmFunction(int sigNumb, siginfo_t *si, void *uc)
		{
			// get the pointer out of the siginfo structure and asign it to a new pointer variable
			Timer *ptrTimer = reinterpret_cast<Timer *> (si->si_value.sival_ptr);
			// call the member function
			ptrTimer->onTimeout();
		}


	private:
		F onTimeout;
};

template<typename F>
Timer<F> CreateTimer(int seconds, F callback)
{
    return Timer<F>(callback, seconds);
}


int main( int argc, char *argv[] )
{
	printf("Creating timer...\n");
	auto timer = CreateTimer(1, []{ std::cout << "TRIGGERED!" << std::endl; });
	printf("Done Creating timer...\n");
    timer.start();

	sleep(5);
}

#include <chrono>
#include <iostream>
#include <thread>


void runCounter( const unsigned id, unsigned counter )
{
      //  unique identifier of the thread
	const auto pid = std::this_thread::get_id();

	std::cout << id <<":"<< pid <<": countdown:" << std::endl;
	for(  ; counter > 0 ; --counter )
	{
		std::cout << id << ": " <<  counter << '\n';
		  // stop current thread until at least 1 second
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << id << ": Lift off!" << std::endl;
}

int main()
{
	const unsigned id = 1024;
 {
	std::thread th1(runCounter, 8091, 5); // start new thread

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	runCounter(id, 2);

	  // if thread hasn't been joined or detached
	if( th1.joinable() ) {
		std::cout << id << ": waiting for thread finished" << std::endl;
		  // synchronizes the moment this function returns with
		  // the completion of all the operations in the thread
		th1.join();
		  // After a call to this function, the thread object becomes non-joinable
		  // and can be destroyed safely
	}
 }
	std::cout << id << ": exit" << std::endl;

	return 0;
}

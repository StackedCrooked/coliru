#include <boost/thread.hpp>
#include <iostream>

using namespace boost;

int main() {
    thread t([]{
            int i = 0;
    		while (true) try {
				if (i >= 10) return;
				while (i < 10) {
					this_thread::sleep_for(chrono::milliseconds(200));
					std::cout << "processed " << i++ << "\n";
				}
			}
			catch (...) { std::cout << "Interrupted at i = " << i << "\n"; }
	});

	this_thread::sleep_for(chrono::milliseconds(800));
	t.interrupt();

	t.join();
	std::cout << "Interrupt requested? : " << std::boolalpha << t.interruption_requested() << "\n";
}

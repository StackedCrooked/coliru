#include <iostream>
#include <thread> 
#include <mutex> 
#include <condition_variable>
using namespace std;

/* Question: Implement the Readers/Writers Problem

Consider a shared database:
- Two classes of users:
- Readers - never modify database
- Writers - read and modify database

Correctness Constraints:
- Readers can access database when no writers
- Writers can access database when no readers or writers
- Only one thread manipulates state variables at a time

Idea:
- Reader()
Wait until no writers
Access database
Check out - wake up a waiting writer

- Writer()
Wait until no active readers or writers
Access database
Check out - wake up waiting readers or writer

- Implementation:
The read operations could overlap in the stdout
*/

class ReaderWriter {
private:
    int AR; // number of active readers
	int WR; // number of waiting readers
	int AW; // number of active writers
	int WW; // number of waiting writers
	mutex lock;
	condition_variable okToRead;
	condition_variable okToWrite;
	int database_variable;

public:
	ReaderWriter() : AR(0), WR(0), AW(0), WW(0), database_variable(0) {}

	void read_lock() {
		unique_lock<mutex> l(lock);

		WR++; // no writers exist
		// is it safe to read?
		okToRead.wait(l, [this](){ return WW == 0 && AW == 0; });
		WR--; // no longer waiting

		AR++;  // now we are active
	}

	void read_unlock() {
		unique_lock<mutex> l(lock);

		AR--; // no longer active

		if (AR == 0 && WW > 0) { // no other active readers
			okToWrite.notify_one(); // wake up one writer
		}
	}

	void write_lock() {
		unique_lock<mutex> l(lock);

		WW++; // no active user exist
		// is it safe to write?
		okToWrite.wait(l, [this](){ return AR == 0 && AW == 0; });
		WW--; // no longer waiting

		AW++; // no we are active
	}

	void write_unlock() {
		unique_lock<mutex> l(lock);

		AW--; // no longer active

		if (WW > 0) { // give priority to writers
			okToWrite.notify_one(); // wake up one writer
		}
		else if (WR > 0) { // otherwize, wake reader
			okToRead.notify_all(); // wake all readers
		}
	}

	void database_thread_write(unsigned int thread_id) {
		for (int i = 0; i < 10; i++) {
			write_lock();

			database_variable++;
			cout << "database_thread_write: " << thread_id << " ... wrote: " << database_variable << endl;

			write_unlock();

			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	void database_thread_read(unsigned int thread_id) {
		for (int i = 0; i < 10; i++) {
			read_lock();

			cout << "database_thread_read: " << thread_id << " ... read: " << database_variable << endl;

			read_unlock();

			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
};

int main() {
	// your code goes here
	ReaderWriter rw;

	thread w1(&ReaderWriter::database_thread_write, &rw, 0);
	thread r1(&ReaderWriter::database_thread_read, &rw, 1);
	thread r2(&ReaderWriter::database_thread_read, &rw, 2);
	thread r3(&ReaderWriter::database_thread_read, &rw, 3);

	w1.join();
	r1.join();
	r2.join();
	r3.join();

	cout << "\nThreads successfully completed..." << endl;

	return 0;
}
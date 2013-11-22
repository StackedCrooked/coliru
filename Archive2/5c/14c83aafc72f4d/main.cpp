
#include <iostream>
#include <string>
#include <thread>
#include <algorithm>
#include <memory>
#include <chrono>
using namespace std;

class T
{
public:
    T(int n) : n_(n) { cout << "T()" << endl; }
	~T() { cout << "~T()" << endl; }

	int Get() { return n_; }
	void Set(int n ) { n_ = n; }
private:
	int n_;
};

shared_ptr<thread> GetThread()
{
	T t(10);

	auto fn = [&]() {
		cout << "thread start : " << t.Get() << endl;
		this_thread::sleep_for(chrono::seconds(5));
		cout << "sleep after : " << t.Get() << endl;
	};

	shared_ptr<thread> sp(new thread(fn));
	return sp;
}



int main()
{
	shared_ptr<thread> sp = GetThread();
	cout << "wait.." << endl;
	sp->join();

	return 0;
}


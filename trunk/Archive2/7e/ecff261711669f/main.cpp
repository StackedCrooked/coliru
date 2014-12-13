#include <mutex>
#include <iostream>
#include <thread>

using namespace std;

mutex m;

class lock_stream_t
{
	std::ostream& ref;
	lock_guard<mutex> l;
public:
	lock_stream_t(std::ostream& r)
		: ref(r), l(m)
	{}
	template <typename T>
	lock_stream_t& operator<<(const T& x)
	{
		ref << x;
		return *this;
	}
	operator std::ostream& () const
	{
		return ref;
	}
};
lock_stream_t* lock_stream() { return nullptr; }

inline lock_stream_t operator<<(std::ostream& out, lock_stream_t* (*)())
{
	return {out};
}

int main()
{
	thread t1([](){
		cout << lock_stream << "ciao1 " << "dal thread 1 " << "concateno1\n";
	});
	
	thread t2([](){
		cout << lock_stream << "ciao2 " << "dal thread 2 " << "concateno2\n";
	});
	
	t1.join();t2.join();
}
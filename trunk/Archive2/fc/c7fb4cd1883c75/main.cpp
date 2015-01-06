#include <iostream>
#include <memory>

using namespace std;


template <class T>
struct PointerManager
{
    typedef shared_ptr<T> Ptr;
	Ptr ptr;

	PointerManager<T>() : ptr(Ptr())
	{};

	void obtain(Ptr ptr_)
	{
		ptr = ptr_;
	}

	Ptr release()
	{
		Ptr temp = ptr;
		ptr.reset();
		return temp;
	}

};


struct Obstacle: PointerManager<Obstacle>
{	
	static Ptr create_shared();
	~Obstacle()
	{cout << "DIE" << endl;};
};

// Create a managed instance of an obstacle 
Obstacle::Ptr Obstacle::create_shared()
{
	Ptr ob = Ptr(new Obstacle);
	ob->obtain(ob);
	return ob;
};

int main() {
	// your code goes here
	Obstacle::Ptr pointer = Obstacle::create_shared();
	pointer->release();
	cout << "DONE, on exit we should see DIE printed"<< endl;
	return 0;
}
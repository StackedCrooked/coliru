#include <iostream>
// #include <boost/noncopyable.hpp>

struct Singleton // : private boost::noncopyable
{
public:   
    static Singleton& getInstance();
	void showMessage() const ; // ****
	int i;

private: 
	Singleton(){i = 7; };
	
	// Singleton(const Singleton &) = delete;  
	// Singleton(Singleton&&) = delete; 
    Singleton(const Singleton &) ; // declared private, not defined
	
	
	// Singleton& operator=(const Singleton&) = delete;
	// Singleton& operator=(Singleton&&) = delete;
	Singleton& operator=(const Singleton&) ; // declared private, not defined
};

const int bg = Singleton::getInstance().i ;

Singleton & Singleton::getInstance()
{
  // caveat: legacy c++ is not concurrency aware
  // there could be a race-condition if multiple threads are involved
  static Singleton  Instance; 
  return Instance;
}

void Singleton::showMessage() const // ****
{
   std::cout << "Hello World, this is a Meyer Singleton Design Pattern\n" ; // << std::endl;
}

int g = Singleton::getInstance().i;

int main()
{

	std::cout << bg << ' ' << g << '\n' ; // std::endl;
    Singleton::getInstance().showMessage() ;

	// system("Pause");
    // return 0;
}

#include <iostream>

struct loud
{
    loud() { std::cout << "loud() to " << (void*)this << "\n"; }
	explicit loud(char const* s) { std::cout << "loud(\"" << s << "\") to " << (void*)this << "\n"; }
	loud(loud const& p) { std::cout << "loud(loud const&) from " << (void const*)&p << " to " << (void*)this << "\n"; }
	loud(loud&& p) { std::cout << "loud(loud&&) from " << (void*)&p << " to " << (void*)this << "\n"; }
	void operator=(loud const& p) { std::cout << "operator=(loud const&) from " << (void const*)&p << " to " << (void*)this << "\n"; }
	void operator=(loud&& p) { std::cout << "operator=(loud&&) from " << (void*)&p << " to " << (void*)this << "\n"; }
	~loud() { std::cout << "~loud() at " << (void*)this << "\n"; }
};

#include <vector>

int main()
{
	std::cout << "BEG constructing vector\n";
	std::vector<loud> v;
    v.reserve(5);
    v.assign(3, loud());
	std::cout << "END constructing vector\n";
	
	std::cout << "capacity: " << v.capacity() << "\n\n";
	
	std::cout << "BEG constructing local\n";
	loud const l;
	std::cout << "END constructing local\n\n";
	
	std::cout << "BEG inserting local\n";
	v.insert(v.begin(), l);
	std::cout << "END inserting local\n\n";
    
    std::cout << "BEG emplacing local\n";
    v.emplace(v.begin(), l);
	std::cout << "END emplacing local\n\n";
}
#include <unordered_map>
#include <algorithm>

template<typename F>
class Signal
{
public:

    void connect(void* instance, F function) {
		slot.insert(std::pair<void*, F>(instance, function));
	}

	void disconnect(void* instance) {
		slot.erase(instance);
	}

	void disconnectAll() {
		slot.clear();
	}

	template<class ... Types> void operator()(Types ... args) {
		for(auto it = slot.begin(); it != slot.end(); it++)
			(void) it->second(args...);
	}

private:

	std::unordered_multimap<void*, F> slot;
};

#include <iostream>

int main()
{
	typedef void(*TwoInts)(int, int);
	Signal<TwoInts> signal;

	std::cout << "Connect..." << std::endl;
	signal.connect(nullptr, [] (int a, int b) { std::cout << (a + b) << std::endl; } );
	signal.connect(nullptr, [] (int a, int b) { std::cout << (a * b) << std::endl; } );
	signal.connect(&signal, [] (int a, int b) { std::cout << (a | b) << std::endl; } );
	signal(2,3);
	signal(3,4);

	std::cout << "Disconnect nullptr..." << std::endl;
	signal.disconnect(nullptr);
	signal(2,3);
	signal(3,4);

	std::cout << "Disconnect signal address..." << std::endl;
	signal.disconnect(&signal);
	signal(2,3);
	signal(3,4);
}

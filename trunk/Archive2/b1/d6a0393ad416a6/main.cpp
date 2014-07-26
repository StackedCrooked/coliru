#include <deque>
#include <iostream>
using namespace std;

struct Mullet {
    Mullet(int i) : i(i) { cout << "Mullet()\n"; }
	Mullet(const Mullet &mullet) : i(mullet.i) { cout << "Mullet(const Mullet &)\n"; }
	Mullet(const Mullet &&mullet) : i(mullet.i) { cout << "Mullet(const Mullet &&)\n"; }
	~Mullet() { cout << "~Mullet()\n"; }

	void operator =(const Mullet &mullet) = delete;
	void operator =(const Mullet &&mullet) = delete;

	int i;
};

template<typename T>
typename T::value_type pop_front_return(T &container){
	auto retVal = container.front();
	container.pop_front();
	return retVal;
}

template<typename T>
typename T::value_type pop_front_return2(T &container) {
	auto retVal = std::move(container.front());
	container.pop_front();
	return retVal;
}

int main() {
	std::deque<Mullet> mullets;
	cout << "3x emplace_back\n";
	mullets.emplace_back(1);
	mullets.emplace_back(2);
	mullets.emplace_back(3);
	
	cout << "front: " << mullets.front().i << '\n';

	cout << "pop_front\n";
	mullets.pop_front();

	cout << "pop_front_return\n";
	cout << pop_front_return(mullets).i << '\n';
	
	cout << "pop_front_return2\n";
	cout << pop_front_return2(mullets).i << '\n';
}

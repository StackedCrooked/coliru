#include <chrono>
#include <random>

//seed → mt19937 (the sequence of numbers the twister will produce depends on the initial seed)

//mt19937 → 0 ≤ n ≤ 2^64-1
//↓ uniform_int_distribution{min, max}
//min ≤ n ≤ max

//in a perfect world one would
//seed the rng with a pure random value: `std::random_device{}()`
//but since this doesn’t work as expected with gcc on windows, we use the current time instead
static std::mt19937 random_number_generator{//our mersenne twister, expects uint64 as seed
    static_cast<decltype(std::mt19937::default_seed)>(//int64 → uint64
        std::chrono::high_resolution_clock::now().time_since_epoch().count()//the current time (int64)
    )//one could omit the static_cast if () instead of {} would be used (which allows the conversion implicitly)
};//but we want to be explicit about our conversions

//a constrained view of random numbers
class dice {
private:
    std::uniform_int_distribution<int> distribution;//we want a distribution which produces variables of type int
public:
	dice(int min = 1, int max = 6) : distribution{min, max} {//initialize the distribution, defaults to 1 ≤ n ≤ 6
		//we have nothing else to do here
	}
	int roll() {
		return distribution(random_number_generator);//filter the twister through the distribution
	}
	//we also get implicitly generated: 
	//a destructor (dtor)
	//a copy constructor (cctor) – we can create copies with `dice oneDice = otherDice;` and our distribution gets copied
	//an assignment operator (op=) – `otherDice = oneDice`, to replace the distribution in `otherDice` with the one of `oneDice`
	//and finally also a move constructor and a move assignment operator
};

int main() {
	return 0;
}
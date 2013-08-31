#include <functional>
#include <iostream>
#include <vector>

namespace nmon {

    class Neuromon {
	public:
		Neuromon();
		float fullness;

		void think();

	private:
		std::vector<std::function<double()>> senses;
		double hunger();

		std::vector<std::function<void(double)>> abilities;
		void move_forward(double);
		void turn(double);
	};
}

namespace nmon {

    Neuromon::Neuromon() {
		std::cout << this << std::endl;
		senses.push_back(std::bind(&Neuromon::hunger, *this));

		abilities.push_back(std::bind(&Neuromon::move_forward, *this, std::placeholders::_1));
		abilities.push_back(std::bind(&Neuromon::turn, *this, std::placeholders::_1));
	}

	void Neuromon::think() {
		std::cout << this << std::endl;
		std::vector<double> input;
		for(size_t i = 0; i < senses.size(); ++i) {
			input.push_back(senses[i]());
		}
		
		std::vector<double> output = input;
		for(size_t i = 0; i < abilities.size(); ++i) {
			abilities[i](output[i]);
		}
	}

	double Neuromon::hunger() {
		if(fullness != 0.0f)
			return 1.0f / fullness;
		else
			return 0.0f;
	}

	void Neuromon::move_forward(double) {
	}

	void Neuromon::turn(double) {
	}
}


int main() {
    nmon::Neuromon n;
    n.think();
}

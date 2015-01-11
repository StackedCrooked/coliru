#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

class Meal {
public:
    int p, c,f;

	Meal() {
		p=0;
		c=0;
		f=0;
	}
	Meal(int a, int b, int e) : p(a), c(b), f(e){};

	bool isNull() {
		if( (p == 0) && (c == 0) && (f == 0) ) return true;
		return false;
	}

	bool isNeg() {
		if( (p < 0) || (c < 0) || (f < 0) ) return true;
		return false;
	}

	Meal operator-(const Meal& m) {
		Meal a;
		a.p = p - m.p;
		a.c = c - m.c;
		a.f = f - m.f;
		return a;
	}
private:
    friend bool operator<( const Meal& lhs, const Meal& rhs ) { return ( 
    	(lhs.p < rhs.p) || ( 
    		(lhs.p == rhs.p) && ( 
    			(lhs.c < rhs.c)  || ( 
    				(lhs.c == rhs.c) && (lhs.f < rhs.f)
    				) 
    			) 
    		) 
    	); }
};

int main() {
	int probs;
	scanf("%d", &probs);

	int p_max, c_max, f_max, meals;

	for(int i = 1; i <= probs; ++i) {

		std::cout << "Case #" << i << ": ";

		std::cin >> p_max;
		std::cin >> c_max;
		std::cin >> f_max;
		std::cin >> meals;

		//read in all meals
		std::vector<Meal> vec_meals;
		for(int i = 0; i < meals; ++i) {
			int p,c,f;
			std::cin >> p;
			std::cin >> c;
			std::cin >> f;
			vec_meals.emplace_back(p,c,f);
		}

		bool result = false;
		if(vec_meals.size() > 1) {
			do {
				Meal mealtmp = Meal(p_max, c_max, f_max); //the goal we want
				for(auto a : vec_meals) {
					mealtmp = mealtmp - a;

					if(mealtmp.isNull()) {
						result = true;
						break;
					}
					if(mealtmp.isNeg()) break;
				}

				if(result) break;
			} while(std::next_permutation(vec_meals.begin(), vec_meals.end()));
		} else { //we have 1 meal only
			Meal mealtmp = Meal(p_max, c_max, f_max);
			mealtmp = mealtmp - vec_meals[0];
			if(mealtmp.isNull()) result = true;
		}

		if(result)
			std::cout << "yes" << std::endl;
		else
			std::cout << "no" << std::endl;
	}

	return 0;
}

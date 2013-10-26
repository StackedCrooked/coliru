#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <climits>

int main() {
    std::vector<int> input;
    {
        constexpr int number_of_elements = 1E5;
        std::random_device rd;
        std::mt19937 gen( rd() );
        std::uniform_int_distribution<> dist;
        for(int i = 0; i < number_of_elements; ++i) input.push_back( dist(gen) );
    }
	
	/**
	 * Sorts the array lexicographically.
	 * 
	 * The trick is that we have to compare digits left-to-right
	 * (considering typical Latin decimal notation) and that each of
	 * two numbers to compare may have a different number of digits.
	 * 
	 * This probably isn't very efficient, so I wouldn't do it on
	 * "millions" of numbers. But, it works...
	 */
	std::sort(
		std::begin(input),
		std::end(input),
		[](const int lhs, const int rhs) -> bool {
			static const double limit = .5 * (log(INT_MAX) - log(INT_MAX-1));
			
			const double lx = log10(lhs);
			const double ly = log10(rhs);
			const double fx = lx - floor(lx);  // Get the mantissa of lx.
			const double fy = ly - floor(ly);  // Get the mantissa of ly.
			return fabs(fx - fy) < limit ? lx < ly : fx < fy;
		}
	);
}

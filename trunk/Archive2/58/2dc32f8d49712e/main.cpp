// Permutation.cpp : Defines the entry point for the console application.
//

#include <tuple>
#include <vector>
#include <iostream>
#include <array>
#include <set>
#include <numeric>

template<typename Range>
typename Range::value_type sum(const Range& r) {
    using namespace std;
	return accumulate(begin(r), end(r), typename Range::value_type());
}

const int n = 4;
const int d = 256;

using Combination = std::array<int, n>;

bool operator<(const Combination& x, const Combination& y) {
	return sum(x) < sum(y);
}

int main(int argc, char* argv[])
{
	std::set<Combination> all;
	Combination c{}; // must value initialize a std::array to zero-init its int values
	for (int pos = 0; pos != n; ++pos) {
		for (int i = 0; i != d; ++i) {
			c[pos] = i; // c[0] from 0..d (remains at d), then c[1] from 0..d, etc.
			all.insert(c);
		}
	}
	using std::cout;
	for (const auto& c : all) {
		cout << "[";
		bool first = true;
		for (const auto& v : c) {
			if (!first) {
				cout << ", ";
			}
			first = false;
			std::cout << v;
		}
		cout << "]\n";
	}
	cout << "Number of combinations: " << all.size() << "\n";
	cout << "Lowest sum: " << sum(*begin(all)) << "\n";
	cout << "Highest sum: " << sum(*--end(all)) << "\n";
	return 0;
}


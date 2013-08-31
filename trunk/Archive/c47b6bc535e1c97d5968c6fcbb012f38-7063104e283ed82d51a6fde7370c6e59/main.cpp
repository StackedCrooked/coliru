#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>
#include <cstddef>

using namespace std;

int main()
{
    vector<string> words;
	vector<size_t> len;

	words.push_back("Hello");
	words.push_back("There");
	words.push_back("You");
	words.push_back("Noob");

	transform(words.begin(), words.end(), back_inserter(len), mem_fn(&string::size));

	for (auto x : len)
		std::cout << x << std::endl;

	cin.get();
	return 0;
}
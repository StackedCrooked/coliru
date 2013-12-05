#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;


string genRandom(size_t length) {
	static const char alphanum[] =
		"0123456789"
		"!@#$%^&*"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	string result; 
	result.reserve(length);

	for (auto i = 0u; i < length; ++i) {
		result.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
	}

	return result;
}

void simulateMoveOperations(vector<string>& src)
{
    vector<string> dest;
    dest.reserve(src.size());

	auto start = chrono::high_resolution_clock::now();
	
	for_each(make_move_iterator(begin(src)), make_move_iterator(end(src)), [&](string&& tmp){
		dest.emplace_back(move(tmp));
	});
	
	auto end = chrono::high_resolution_clock::now();
	cout << "move: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " micros" << endl;
}

void simulateCopyOperations(vector<string>& src)
{
    vector<string> dest;
    dest.reserve(src.size());

	auto start = chrono::high_resolution_clock::now();
	
	for(const auto& s : src)
	    dest.emplace_back(s);
	
	auto end = chrono::high_resolution_clock::now();
	cout << "copy: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " micros" << endl;
}

int main()
{
    vector<string> src;
	src.resize(1000000);
	generate(begin(src), end(src), [](){
		return genRandom(200u);
	});

    simulateCopyOperations(src);
    simulateMoveOperations(src);
}


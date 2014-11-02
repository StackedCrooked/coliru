#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <regex>

using namespace std;

int main()
{
    vector<string> texts;
	fstream file("F:\\test.txt");
	if (file.is_open())
	{
		string test;
		while (getline(file, test))
			texts.push_back(test);
	}
	vector<string> res;
	vector<string> texts2 = texts;
	std::smatch m;
	std::regex e("\\b(ea)([^ ]*)");
	auto start = chrono::steady_clock::now();
		for (auto& i : texts){
			while (std::regex_search(i, m, e)) {
				for (auto x : m) res.push_back(x);
				i = m.suffix().str();
			}
		}
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << chrono::duration <double, milli>(diff).count() << " ms\n";

	cout<<'\n'<<res.size()<<"\n\n";
	res.clear(); res.shrink_to_fit();
	texts = texts2;


	//test 2
	start = chrono::steady_clock::now();
	for (auto& i : texts){
		auto first = i.cbegin();
		auto last = i.cend();
		while (std::regex_search(first,last,m,e)) {
			for (auto x : m) res.push_back(x);
			first = m.suffix().first;
		}
	}

	end = chrono::steady_clock::now();
    diff = end - start;
	cout << chrono::duration <double, milli>(diff).count() << " ns\n";
	return 0;
}
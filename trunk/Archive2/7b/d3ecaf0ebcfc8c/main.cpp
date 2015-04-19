#include <vector>
#include <regex>
#include <iterator>
#include <iostream>
#include <fstream>
#include <future>

struct result {
    std::string file_name;
	std::vector<std::string> data;
	friend std::ostream &operator<<(std::ostream &os, result const &r) {
		if (!r.data.empty()) {
			os << r.file_name << "\n";
			for (auto const &s : r.data)
				os << "\t" << s << "\n";
		}
		return os;
	}
};

result do_grep(std::regex &r, std::string const &filename) {
	result results;
	results.file_name = filename;
	std::ifstream in(filename);

	std::string temp;
	for (int i = 0; std::getline(in, temp); i++)
		if (std::regex_search(temp, r))
			results.data.emplace_back(temp);
	return results;
}

int main(int argc, char **argv) { 
	if (argc < 3) {
		std::cerr << "Usage: grep <pattern> <filename> [filename ...]\n";
		return 1;
	}

	std::vector<std::future<result>> results;

	std::regex r(argv[1]);
	for (int i = 2; i < argc; i++)
		results.emplace_back(std::async(std::launch::async, do_grep, r, argv[i]));

	for (auto &match : results) {
		match.wait();
		std::cout << match.get() << "\n";
	}
}

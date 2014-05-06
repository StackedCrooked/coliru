#include <iostream>
#include <vector>

void algo(std::vector<std::vector<int> >& result, std::vector<int> path, std::vector<int> tasks);

int main()
{
    std::vector<int> v { 1, 2, 3, 4 };
	std::vector<std::vector<int> > res;
	algo(res, std::vector<int>(), v);

	for(auto const& vec : res) {
		for(auto e : vec) {
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}

void algo(std::vector<std::vector<int> >& result, std::vector<int> path, std::vector<int> tasks)
{
	for(auto it = std::begin(tasks), itend = std::end(tasks) ; it != itend ; ++it) {
		std::vector<int> temp(std::begin(tasks), it);
		std::copy(it + 1, itend, std::back_inserter(temp));

		path.push_back(*it);
		result.push_back(path);
		algo(result, path, temp);
		path.pop_back();
	}
}
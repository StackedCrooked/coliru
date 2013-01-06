#include <memory>
#include <array>
#include <tuple>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

class MoveMeMaybe
{
public:
    std::unique_ptr<int> p;

	MoveMeMaybe() { }
	~MoveMeMaybe() { }

	MoveMeMaybe(MoveMeMaybe&& m): p(std::move(m.p)) { }
	MoveMeMaybe& operator=(MoveMeMaybe&& m) { p = std::move(m.p); return *this; }


private:
	MoveMeMaybe(const MoveMeMaybe&);
	MoveMeMaybe& operator=(const MoveMeMaybe&);
};

int main()
{
	std::vector<MoveMeMaybe> v;
	
	MoveMeMaybe m;
	m.p = std::unique_ptr<int>(new int(5));

	v.push_back(m);
}
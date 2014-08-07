#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include <unordered_map>
#include <utility>

typedef size_t max_align_t;

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/global_fun.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

using namespace std;

#define DBG(x) { cout << setw(50) << left << #x << boolalpha << (x) << endl; }

struct Point2D{
    struct ID{};
	struct Hash{};

	unsigned x, y;
};

unsigned myhash(Point2D const& p) {
	return (p.x << 16) + p.y;
}

unsigned myhash_on_pair(pair<int,Point2D> const& p){
	return myhash(p.second);
}

ostream& operator<<(ostream& o, Point2D const& p){
	o << "Point2D{ " << p.x << ", " << p.y << "}";
	return o;
}

namespace mi = boost::multi_index;

typedef boost::multi_index_container<
	pair<int,Point2D>,
	mi::indexed_by<
		mi::hashed_non_unique<
			mi::tag<Point2D::ID>,
			mi::member<pair<int,Point2D>,int,&pair<int,Point2D>::first>
		>,
		mi::ordered_non_unique<
			mi::tag<Point2D::Hash>,
			mi::global_fun<pair<int,Point2D> const&, unsigned, &myhash_on_pair>
		>
	>
> custom_map;

constexpr unsigned elementow = 1000000;

void multiindex()
{
	custom_map m;

	// dodanie elementow
	for(unsigned i = 0; i < elementow*3; i+=3){
		m.insert({i, {i+1, i+2}});
	}

	// znalezienie na 2 sposoby
	for(unsigned i = 0; i < elementow*3; i+=3){
		auto it = m.get<Point2D::ID>().find(i);
		m.get<Point2D::Hash>().find(myhash(it->second));
	}

	// kasowanie
	while(m.size()){
		m.get<Point2D::Hash>().erase(m.get<Point2D::Hash>().begin());
	}
}

void mapy()
{
	map<unsigned, Point2D> posortowana_hash;
	unordered_map<unsigned, Point2D*> id;

	// dodanie elementow
	for(unsigned i = 0; i < elementow*3; i+=3){
		Point2D n{i+1, i+2};
		id[i] = &(posortowana_hash[myhash(n)] = n);
	}

	// znalezienie na 2 sposoby
	for(unsigned i = 0; i < elementow*3; i+=3){
		auto it = id.find(i);
		posortowana_hash.find(myhash(*it->second));
	}

	// kasowanie
	while(id.size()){
		auto it = id.begin();
		posortowana_hash.erase(myhash(*it->second));
		id.erase(it);
	}
}

template<typename T>
chrono::milliseconds measureExecutionTime(T&& f)
{
	auto start = chrono::high_resolution_clock::now();
	f();
	return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start);
}

int main()
{
	DBG(measureExecutionTime(multiindex).count());
	DBG(measureExecutionTime(mapy).count());
}

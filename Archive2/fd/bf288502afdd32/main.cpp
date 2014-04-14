#include <iostream>
#include <boost/mpl/int.hpp>
#include <boost/mpl/next.hpp>
#include <utility>

using namespace boost;

using NumRows = mpl::int_<10>;
using NumCols = mpl::int_<5>;

template<typename Row, typename Col>
struct Switch : private Switch<Row, typename mpl::next<Col>::type> {
    using Switch<Row, typename mpl::next<Col>::type>::case_;
	static std::pair<int, int> case_(Row, Col) {
		return std::make_pair(Row::value, Col::value);
	}
};

template<typename Row>
struct Switch<Row, NumCols> : private Switch<typename mpl::next<Row>::type, mpl::int_<0>>{
	using Switch<typename mpl::next<Row>::type, mpl::int_<0>>::case_;
};

template<>
struct Switch<NumRows, NumCols> {
	static std::pair<int, int> case_(NumRows, NumCols) = delete;
};

using SmartSwitch = Switch<mpl::int_<0>, mpl::int_<0>>;

int main(int argc, char** argv) {
	
	auto k = SmartSwitch::case_(mpl::int_<7>(), mpl::int_<3>());
	std::cout << "(" << k.first << ", " << k.second << ")" << std::endl;
	
	std::cin.get();
	return 0;
}
struct int_wrapper {
    int num;
};

template < typename base, unsigned int tag >
struct disambiguated_wrapper : base {
	using base::base;
};

template <unsigned int N>
struct improvised_container :
	protected disambiguated_wrapper<int_wrapper, N>,
	protected improvised_container<N - 1> {

	unsigned int size() const { return N; }

	int& at(const unsigned int index) {
		if (index >= N) throw "out of range";
		else return (index == N - 1) ?
			this->disambiguated_wrapper<int_wrapper, N>::num :
			this->helper(index);
	}
protected:
	int& helper(const unsigned int index) {
		return (index == N - 1) ?
			this->disambiguated_wrapper<int_wrapper, N>::num :
			this->improvised_container<N - 1>::helper(index);
	}
};


// specializations.h

template <>
struct improvised_container<0> {
	improvised_container() = delete;
}; // ^ prohibits 0-length container

template <>
struct improvised_container<1> :
protected disambiguated_wrapper<int_wrapper, 1>{

	unsigned int size() const { return 1; }

	int& at(const unsigned int index) {
		if (index != 0) throw "out of range";
		else return this->disambiguated_wrapper<int_wrapper, 1>::num;
	}
protected:
	int& helper(const unsigned int index) {
		if (index != 0) throw "out of range";
		else return this->disambiguated_wrapper<int_wrapper, 1>::num;
	}
};
// main.cpp


#include <iostream>

int main() {
	improvised_container<5> my_container;
	for (unsigned int i = 0; i < my_container.size(); ++i) {
		my_container.at(i) = i;
		std::cout << my_container.at(i) << ",";
	}   // ^ Output: "0,1,2,3,4,"
}
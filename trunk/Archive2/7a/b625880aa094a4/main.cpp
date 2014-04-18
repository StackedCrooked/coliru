#include<vector>
#include<algorithm>
#include<string>

struct StructA {
    std::string mCommonField;
    std::string mNameAString;
    float mFloatValueA;
};

struct StructB {
    std::string mCommonField;
    std::string mNameBString;
    int mIntValueB;
};

struct StructC {
    std::string mCommonField;
	std::string mNameFromA = "[]";
	std::string mNameFromB = "[]";
	float mFloatFromA = 0;
	int mIntFromB = 0;

	StructC(const StructA& a) : mCommonField{a.mCommonField},
		mNameFromA{a.mNameAString}, mFloatFromA{a.mFloatValueA} {}

	StructC(const StructB& b) : mCommonField{b.mCommonField},
		mNameFromB{b.mNameBString}, mIntFromB{b.mIntValueB} {}
};

#include <iostream>
#include <iterator>

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, StructC const& sc)
{
	return os <<
		sc.mCommonField << " - " <<
		sc.mNameFromA << " - " << sc.mNameFromB << " - " <<
		std::fixed << sc.mFloatFromA << " - " << sc.mIntFromB <<
	std::endl;
}

struct Comparator
{
	template<typename A, typename B>
	bool operator()(const A& a, const B& b) const
	{
		return a.mCommonField < b.mCommonField;
	}
};

int main() {
	Comparator comparator;

	// initially unsorted list of StructA
	std::vector<StructA> aStructs = {
		{"hello", "nameA1", 1.0f},
		{"goodbye", "nameA2", 2.0f},
		{"foo", "nameA3", 3.0f}
	};

	// initially unsorted list of StructB
	std::vector<StructB> bStructs = {
		{"hello", "nameB1", 10},
		{"goodbye", "nameB2", 20},
		{"bar", "nameB3", 30}
	};

	// in the above list, "hello" & "goodbye" are the common in both aStructs & bStructs

	// pre-sort both sets before calling std::intersection
	std::sort(aStructs.begin(), aStructs.end(), comparator);
	std::sort(bStructs.begin(), bStructs.end(), comparator);

	std::vector<StructC> intersection;
	std::set_intersection(
		aStructs.begin(), aStructs.end(),
		bStructs.begin(), bStructs.end(),
		std::back_inserter(intersection),
		comparator
	);

	std::copy(
		intersection.begin(), intersection.end(),
		std::ostream_iterator<StructC>(std::cout, "")
	);

	return 0;
}


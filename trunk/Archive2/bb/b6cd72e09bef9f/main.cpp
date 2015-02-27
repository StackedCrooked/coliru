#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <boost/serialization/vector.hpp>

using namespace std;

class form_mesto
{
private:
    friend class boost::serialization::access;
	template<class Archieve>
	void serialize(Archieve&ar, const unsigned int version)
	{
		// ...
	}
public:
	string mesto;
	int year;
	int mounth;
	int day;
	bool visit = false;
	form_mesto(string a_mesto)
	{
		mesto = a_mesto;
	}
};

class Place
{
private:
	friend class boost::serialization::access;
	template<class Archieve>
	void serialize(Archieve&ar, const unsigned int version)
	{
		ar& mesta;
		ar& person;
	}
public:
	string person;
	vector<form_mesto> mesta;

	Place(string a_person)
	{
		person = a_person;
	}

	void add_place(form_mesto a_mesto)
	{
		mesta.push_back(a_mesto);
	}
};

int main()
{
	string input_in_form = "London";
	string input_in_Place = "Eugene";
	form_mesto z = form_mesto(input_in_form);
	Place x = Place(input_in_Place);
	x.add_place(z);
	std::ofstream ofs("save.dat", std::ios::binary);
	boost::archive::binary_oarchive oa(ofs);
	oa << x;
}

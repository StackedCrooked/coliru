#include <string>
#include <memory>
#include <iostream>

using namespace std;

class Library {
private:
    string	m_name;

public:
	Library(string name)
		: m_name(name)
	{
	}

	const string &name() const
	{
		return m_name;
	}

	virtual unique_ptr<Library> clone() const = 0;
	virtual unique_ptr<Library> move() = 0;
};

template <typename Child>
class LibraryBase : public Library
{
public:
	using Library::Library;

	unique_ptr<Library> clone() const override
	{
		return make_unique<Child>(static_cast<const Child &>(*this));
	}

	unique_ptr<Library> move() override
	{
		return make_unique<Child>(::move(static_cast<Child &>(*this)));
	}
};



class Xml : public LibraryBase<Xml> {
public:
	using LibraryBase::LibraryBase;
};

int main(void)
{
	Xml lib("this is xml file");

	cout << "lib.name() " << lib.name() << endl;

	auto lib2 = lib.clone();

	cout << "lib.name() " << lib.name() << endl;
	cout << "lib2.name() " << lib2->name() << endl;

	auto lib3 = lib.move();

	cout << "lib.name() " << lib.name() << endl;
	cout << "lib2.name() " << lib2->name() << endl;
	cout << "lib3.name() " << lib3->name() << endl;

	return 0;
}
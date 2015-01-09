#include <iostream>
#include <string>
#include <algorithm>

struct person_identity
{
    std::string name;
    int ID ;
    person_identity( const std::string& n, int id ) : name(n), ID(id) {}
};

struct person_attributes
{
    std::string age ;
    int height, weight;
    person_attributes( std::string age, int h, int w ) : age(age), height(h), weight(w) {}
};

struct Person : private person_identity, private person_attributes {

    Person (const std::string& n, int id, std::string age, int h, int w )
        : person_identity(n,id), person_attributes(age,h,w)  {}

    Person& assignWithExceptions( const Person& other ) { attributes() = other ; return *this ; }
    Person& assignWithExceptions( Person&& other ) { assign_attributes( std::move(other) ) ; return *this ; }

    void print() const {
    	std::cout << "Name = " << name << '\n';
		std::cout << "ID = " << ID << '\n';
		std::cout << "Age = " << age << '\n';
		std::cout << "Height = " << height << '\n';
		std::cout << "Weight = " << weight << "\n\n";
	}

	private:
        void assign_attributes( person_attributes&& attrib ) { std::swap( attributes(), attrib ) ; }
        person_attributes& attributes() { return static_cast<person_attributes&>(*this) ; }
};


int main() {
	Person bob ("Bob", 2047, "38 years 2 months", 183, 170);
	Person frank ("Frank", 5025, "25 years 7 months", 190, 205);
	bob.print();
	frank.print();

	std::cout << "Bob pretends to be Frank, but keeps his name and ID.\n";
	bob.assignWithExceptions (frank);
	bob.print();

	bob.assignWithExceptions( Person( "xxx", 123, "4 years 5 months", 678, 9 ) );
	bob.print();
    
}

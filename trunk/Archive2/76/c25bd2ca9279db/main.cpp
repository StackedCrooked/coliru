#include <iostream>
#include <string>
#include <algorithm>

struct Person {

    std::string name;
    int ID, height, weight;
    std::string age ; // **** changed to std::string to illustrate move
    Person (const std::string& n, int id, std::string age, int h, int w )
        : name(n), ID(id), height(h), weight(w), age(age)  {}

    struct not_excluded_part_of {

        int height, weight;
        std::string age ;
        not_excluded_part_of( const Person& other ) // copy the non-excluded part
            : height(other.height), weight(other.weight), age(other.age) {} // copy string age
        not_excluded_part_of( Person&& other )
            : height(other.height), weight(other.weight), age( std::move(other.age) ) {}
    };

    Person& operator= ( not_excluded_part_of&& ne ) // move-assign the copy of the non-excluded part
    { std::swap(age,ne.age) ; std::swap(height,ne.height) ; std::swap(weight,ne.weight) ; return *this ; } // move string age

    Person& assignWithExceptions( const Person& other ) { return *this = not_excluded_part_of(other) ; }
    Person& assignWithExceptions( Person&& other ) { return *this = not_excluded_part_of( std::move(other) ) ; }

    void print() const {
		std::cout << "Name = " << name << '\n';
		std::cout << "ID = " << ID << '\n';
		std::cout << "Age = " << age << '\n';
		std::cout << "Height = " << height << '\n';
		std::cout << "Weight = " << weight << "\n\n";
	}
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

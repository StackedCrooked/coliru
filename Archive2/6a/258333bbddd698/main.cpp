#include <iostream>
#include <fstream>
#include <typeinfo>

struct Person{

    Person() = default ;
    Person( const Person& that ) : name(that.name) { /* can't copy std::ofstream */ }
    Person( Person&& that ) noexcept = default ;

    private:
	    std::string name;
		std::ofstream PersonFile;
};

class Girl: public Person {};

class Cheerleader: public Girl {
	private:
		int cheeringSkill;
	public:
		Cheerleader () {}
		Cheerleader (const Girl&);  // constructor to allow conversion of Girl to type Cheerleader
};

Cheerleader::Cheerleader (const Girl& girl) {}

int main () {
	Girl Mary;
	std::cout << typeid (Mary).name() << std::endl;
	Cheerleader _Mary = static_cast<Cheerleader> (Mary);
	std::cout << typeid (_Mary).name() << std::endl;  // type cast successful
  	return 0;
}

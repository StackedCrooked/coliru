#include <iostream>
#include <string>
#include <memory>

class Person;  class PersonProxy;

class PersonInterface {
    public:
		virtual ~PersonInterface() = default;
		virtual PersonProxy* getProxy() const = 0;
		virtual void createProxy (Person*) = 0;
};

class Person : public PersonInterface {
	private:
		std::string name;
		std::shared_ptr<PersonProxy> proxy;
	public:
		Person() = default;
		explicit Person (const std::string& name) : name (name) {}
	public:
		virtual PersonProxy* getProxy() const override {return proxy.get();}
		inline void createProxy (Person* p);
};

class PersonProxy : public PersonInterface {
    private:
		std::shared_ptr<Person> actual;
	public:
	    explicit PersonProxy (Person* p) : actual (std::shared_ptr<Person>(p)) {}
		explicit PersonProxy (std::shared_ptr<Person> p) : actual (p) {}
		void rebind (std::shared_ptr<Person> p) {actual = p;}
		virtual PersonProxy* getProxy() const override {return actual->getProxy();}
		virtual void createProxy (Person* p) override {actual->createProxy(p);}
};

class Girl : public Person, public std::enable_shared_from_this<Girl> {
	public:
		Girl (const std::string& name) : Person (name) {createProxy (this);}
        ~Girl() { std::cout << "destroying Girl object at " << this << '\n' ; }
};

inline void Person::createProxy (Person* p) {
	proxy = std::shared_ptr<PersonProxy>(new PersonProxy(p));
}

int main() {
	{
		Girl* a = new Girl("a");
        std::cout << "created the Girl object at: " << a << '\n' ;
		std::shared_ptr<Girl> b = std::make_shared<Girl>("b");
        std::cout << "made shared pointer, about to rebind\n" ;
		a->getProxy()->rebind(b);
		std::cout << "rebind succeeded\n" << std::flush ;
	}
	std::cout << "Exited scope\n" ;   
}   // Crash (with VS2013) because b is deleted twice due to two separate ownership groups. 

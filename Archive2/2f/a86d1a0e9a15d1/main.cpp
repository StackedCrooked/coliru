#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

struct PersonProxy;

struct State {
    virtual ~State() = default;
} *normal = new State;

class Charmed : public State {
	private:
		std::shared_ptr<PersonProxy> charmer;
	public:
		Charmed (std::shared_ptr<PersonProxy> p) : charmer(p) {}
		std::shared_ptr<PersonProxy> getCharmer() const {return charmer;}
};

struct Person : std::enable_shared_from_this<Person> {
    private:
		std::string name_ ;
    	State* state = normal;
    public:
    	virtual ~Person() = default ;
    	virtual std::string getName() const { return "'" + name_ + "'" ; }
    	virtual State* getState() const {return state;}
    	virtual void setState (State* s) {state = s;}
    	virtual void action( /*std::shared_ptr<PersonProxy>,*/ std::shared_ptr<PersonProxy>){}
    	virtual bool isCharmed() const {return dynamic_cast<Charmed*>(state);}
    protected:
        Person() = default;
        explicit Person ( const std::string& name ) : name_(name) {}
	private:
	    Person( const Person& ) = delete ;
	    Person& operator= ( const Person& ) = delete ;
};

struct PersonProxy : Person {
	    static std::shared_ptr<PersonProxy> make( const std::shared_ptr<Person>& p ) {
	        return std::shared_ptr<PersonProxy>( new PersonProxy(p) );
	    }
	    std::shared_ptr<PersonProxy> rebind( const std::shared_ptr<Person>& p ) {
			actual = p;
	        return std::dynamic_pointer_cast<PersonProxy>( shared_from_this() ) ;
	    }
	    virtual std::string getName() const override { return actual->getName(); }
	    virtual State* getState() const override {return actual->getState();}
	    virtual void setState (State* s) override {actual->setState(s);}
	    virtual bool isCharmed() const override {return actual->isCharmed();}
		void action(std::shared_ptr<PersonProxy> p) {
			actual->action(/*std::dynamic_pointer_cast<PersonProxy>(shared_from_this()),*/ p); // **************
		}
    private:
        std::shared_ptr<Person> actual;
        explicit PersonProxy( const std::shared_ptr<Person>& p ) : actual( p ) {}
        bool is_cyclic( const std::shared_ptr<Person>& p ) const {
            auto pp = std::dynamic_pointer_cast<PersonProxy>(p) ;
            if( pp && ( pp.get() == this ) ) return true ;
            else return pp ? is_cyclic( pp->actual ) : false ;
        }
};

struct girl : Person {

    static std::shared_ptr<PersonProxy> make( const std::string& name ) {
        return PersonProxy::make( std::shared_ptr<girl>( new girl(name) ) ) ;
    }
    private:
        girl( const std::string& name ) : Person( name ) {}
        virtual void action( /*std::shared_ptr<PersonProxy>,*/ std::shared_ptr<PersonProxy>) override {} // **************
};

struct Wizard : Person {
    static std::shared_ptr<PersonProxy> make( const std::string& name ) {
        return PersonProxy::make( std::shared_ptr<Wizard>( new Wizard(name) ) ) ;
    }
    void castsCharmSpell ( /*std::shared_ptr<PersonProxy> spellCaster,*/ std::shared_ptr<PersonProxy> target) {
    	target->setState( new Charmed( /*spellCaster*/ PersonProxy::make( shared_from_this() ) ) ); // **************
// std::shared_ptr<PersonProxy> spellCaster has to be passed because Person has no std::shared_ptr<PersonProxy> data member.
// This will have to be done with all functions like castsCharmSpell for derived types of Person.  Good design?
    }
    private:
        Wizard( const std::string& name ) : Person( name ) {}
        virtual void action(/*std::shared_ptr<PersonProxy> instigator,*/ std::shared_ptr<PersonProxy> p) override { // **************
			castsCharmSpell(/*instigator,*/ p);
		}
};

int main() {
    std::shared_ptr<PersonProxy> a = girl::make( "Alice" );
    std::shared_ptr<PersonProxy> wizard = Wizard::make( "Wizard" );
	std::shared_ptr<PersonProxy> b = girl::make( "The queen of hearts" );

    wizard->action(a);
    if (a->isCharmed())
	std::cout << a->getName() << " is charmed by "  << dynamic_cast<Charmed*>(a->getState())->getCharmer()->getName() << "." << std::endl;

    wizard->rebind(b);
    dynamic_cast<Charmed*>(a->getState())->getCharmer()->rebind(b) ; // **************
    std::cout << "'Wizard' has been transformed into " << wizard->getName() << "." << std::endl;
    if (a->isCharmed())
	std::cout << a->getName() << " is charmed by "  << dynamic_cast<Charmed*>(a->getState())->getCharmer()->getName() << "." << std::endl;
}

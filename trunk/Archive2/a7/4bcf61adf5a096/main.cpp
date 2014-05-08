#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <stdexcept>

template <typename T>
std::string toString (const T& t) {
    std::stringstream ss;
	ss << t;
	return ss.str();
}

class LivingBeing {
	public:
        class Memento { // memento has value semantics (MoveConstructible,MoveAssignable)
                std::unique_ptr<LivingBeing> copy;
                Memento( const LivingBeing* being ) : copy( being->clone() ) {}
                friend class LivingBeing ;
	    };

        virtual ~LivingBeing() noexcept = default;
        
	    virtual void change (int, double) = 0;
	    virtual std::string display() const = 0;
        
        // with ploymorphic clone and assign, the base class can implement these
	    virtual Memento createMemento() const { return Memento(this) ; } // return memento by value
	    virtual void restoreMemento ( const Memento& m ) { assign( *m.copy ) ; }
        
	protected:
	    virtual std::unique_ptr<LivingBeing> clone() const = 0;
        virtual LivingBeing& assign ( const LivingBeing& ) = 0 ; // may throw std::bad_cast
};

template <typename DERIVED> // DERIVED class is CopyAssignable
class LivingBeingCRTP: public LivingBeing { // sythesizes overrides for clone() and assign()
    protected:
        virtual std::unique_ptr<LivingBeing> clone() const override 
        {return std::unique_ptr<LivingBeing>( new DERIVED( static_cast<const DERIVED&>(*this) ) );}
        
        virtual LivingBeing& assign ( const LivingBeing& being ) override // may throw std::bad_cast
        { return static_cast<DERIVED&>(*this) = dynamic_cast< const DERIVED& >(being) ; }
};

class Fighter: public LivingBeingCRTP<Fighter> {
    int i = 0;
    double d = 0;
    public:
	    virtual void change (int a, double b) override {i += a; d += b;}
	    virtual std::string display() const override {return "Fighter {" + toString(i) + ", " + toString(d) + "}" ;}
};

class MagicUser: public LivingBeingCRTP<MagicUser> {
    std::string name;
    public: 
    	virtual void change (int a, double b) override {name = toString(a) + toString(b);}
        virtual std::string display() const override {return "MagicUser {" + name + "}";}
};

int main() {
    for (auto& p: {std::unique_ptr<LivingBeing>(new Fighter), std::unique_ptr<LivingBeing>(new MagicUser)})
    {
        p->change (23, 67.89) ;
        std::cout << "first: " << p->display() << std::endl; 
        const auto snapShot = p->createMemento();
        p->change (123, 267.89);
        std::cout << "second: " << p->display() << std::endl;
        p->restoreMemento (snapShot);
        std::cout << "restored: " << p->display() << "\n----------------------------\n";
    }
}
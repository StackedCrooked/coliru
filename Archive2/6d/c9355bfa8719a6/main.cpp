#include <iostream>
#include <string>
#include <typeinfo>
#include <memory>

struct person_visitor ;  // important class

struct person
{
    virtual ~person() = default ;
    virtual std::string name() const = 0 ;
    virtual int age() const = 0 ;
    virtual std::shared_ptr<person> best_friend() const  = 0 ;
    virtual void befriend( std::shared_ptr<person> p ) = 0 ;
    virtual std::string faith() const = 0 ;
    virtual double get_pocket_change() const = 0;
    virtual void add_pocket_change (double change) = 0;

    virtual std::ostream& print( std::ostream& stm = std::cout ) const
    {
        stm << name() << ' ' << age() << " years (" << faith() << ')' ;
        const auto f = best_friend() ;
        if(f) stm << "  best friend: '" << f->name() << "' (" << f->faith() << ')' ;
        stm << std::endl << "pocket change = $" << get_pocket_change() << std::endl;
        return stm << '\n' ;
    }

	virtual bool accept( person_visitor* ) = 0 ;

	// *** removed budhist-specific stuff
};

struct person_visitor {
    virtual~person_visitor() = default ;
	virtual bool visit ( person* p ) = 0 ; // *** changed person_impl* => person*
};

struct person_impl : person
{
    virtual std::string name() const override { return name_ ; }
    virtual int age() const override { return age_ ; }
    virtual std::shared_ptr<person> best_friend() const override { return best_friend_ ; }
    virtual void befriend( std::shared_ptr<person> p ) override { best_friend_ = p ; }
    virtual double get_pocket_change() const override {return pocket_change;}
	virtual void add_pocket_change (double change) override { pocket_change += change;}

    person_impl( std::string name, int age, std::shared_ptr<person> best_friend = {} )
        : name_(name), age_(age), best_friend_(best_friend) {}

    virtual bool accept( person_visitor* v ) override { return v->visit(this) ; }

    private:
        const std::string name_ ;
        int age_ ;
        double pocket_change = 0;  // pocket_change is an always-changing value which should not be in the constructor
        std::shared_ptr<person> best_friend_ ;

        template < typename T >
		std::shared_ptr<person_impl> convert ( std::string new_name ) {
		    auto p = std::make_shared<T>( new_name.empty() ? name_ : new_name, age_, best_friend_ ) ;
		    p->add_pocket_change(pocket_change) ; // *** added
			return  p ;
		}
        friend struct person_proxy ;
};

struct person_proxy : person
{
  private:
    std::shared_ptr<person_impl> actual ;
  public:
    virtual std::string name() const override { return actual->name() ; }
    virtual int age() const override { return actual->age() ; }
    virtual std::shared_ptr<person> best_friend() const override { return actual->best_friend() ; }
    virtual void befriend( std::shared_ptr<person> p ) override { actual->befriend(p) ; }
    virtual std::string faith() const override { return actual->faith() ; }
    virtual double get_pocket_change() const override {return actual->get_pocket_change();}
	virtual void add_pocket_change (double change) override {actual->add_pocket_change (change);}
	virtual bool accept( person_visitor* v ) { return actual->accept(v) ; } // *** added

    explicit person_proxy( std::shared_ptr<person_impl> p ) : actual(p) {}
    void rebind( std::shared_ptr<person_impl> p ) { actual = p ; }

    template< typename T, typename... ARGS >
	static std::shared_ptr<person_proxy> make( ARGS&&... args )
    { return std::make_shared<person_proxy>( std::make_shared<T>( std::forward<ARGS>(args)... ) ) ; }

    template < typename T >
	void convert( std::string new_name = "" ) {
		rebind( actual->convert<T>(new_name) ) ;
	}
};

#define DEFINE_PERSON(denomination) \
struct denomination : person_impl \
{ \
    using person_impl::person_impl ; \
    virtual std::string faith() const override { return #denomination ; } \
};

DEFINE_PERSON(wasp)
DEFINE_PERSON(muslim)
DEFINE_PERSON(agnostic)
DEFINE_PERSON(hindu)

struct buddhist : person_impl
{
  private:
	std::string mala_colour = "red";
  public:
    using person_impl::person_impl ;
    virtual std::string faith() const override { return "buddhist" ; }

	virtual std::string get_mala_colour() const {return mala_colour;}
};

struct mala_colour_visitor : person_visitor {
	virtual bool visit( person* p ) override
	{
	    auto b = dynamic_cast<buddhist*>(p) ;
	    if(b)
        {
            mala_colour = b->get_mala_colour() ;
            return true ;
        }
        else return false ;
	}
	std::string mala_colour ; // *** to hold the result
};

template < typename T > struct reincarnation_visitor : person_visitor {
	virtual bool visit( person* p ) override
	{
	    auto b = dynamic_cast<buddhist*>(p) ;
	    if(b)
        {
            std::cout << p->name() << " has reincarnated to a " << typeid(T).name() << ".\n" ;
            return true ;
        }
        else return false ;
	}
};

struct dog {};

int main()
{
    std::shared_ptr<person_proxy> mary = person_proxy::make<wasp>( "Mary", 28 ) ;
    std::shared_ptr<person_proxy> sandy = person_proxy::make<wasp>( "Sandy", 23, mary ) ;
    mary->befriend(sandy) ;
    mary->add_pocket_change (12.38);
    sandy->add_pocket_change (2.55);
    mary->print() ;
    sandy->print() ;
    std::cout << "------------------\n" ;

    sandy->convert<muslim>("Fatima") ;
    mary->print() ;
    sandy->print() ;
    std::cout << "------------------\n" ;

    mary->convert<agnostic>("Orchid") ;
    sandy->convert<hindu>("Deepika") ;
    mary->print() ;
    sandy->print() ;
    std::cout << "------------------\n" ;

    mary->convert<buddhist>("Priya");
    mary->print() ;
    sandy->print() ;

    mala_colour_visitor mcv ;
    if( sandy->best_friend()->accept(&mcv) )
    {
        std::cout << sandy->best_friend()->name() << ", a "
                   << sandy->best_friend()->faith() << ", is wearing a "
                   << mcv.mala_colour << " mala on her wrist.\n" ;
    }


	reincarnation_visitor<dog> rv ;
    sandy->best_friend()->accept(&rv);
}

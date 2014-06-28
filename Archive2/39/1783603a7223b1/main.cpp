#include <iostream>
#include <string>
#include <typeinfo>
#include <memory>

struct person
{
    // struct visitor { virtual ~visitor() = default ; } ;

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

    // virtual bool accept( person::visitor& ) {} ;
	// bool accept( person::visitor&& v ) { return accept(v) ; } // forward to virtual
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

    private:
        const std::string name_ ;
        int age_ ;
        double pocket_change = 0;
        std::shared_ptr<person> best_friend_ ;

        template < typename T >
		std::shared_ptr<person_impl> convert ( std::string new_name ) {
		    auto p = std::make_shared<T>( new_name.empty() ? name_ : new_name, age_, best_friend_ ) ;
		    p->add_pocket_change(pocket_change) ;
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

    explicit person_proxy( std::shared_ptr<person_impl> p ) : actual(p) {}
    void rebind( std::shared_ptr<person_impl> p ) { actual = p ; }

    template < typename T > static std::shared_ptr<T> cast( std::shared_ptr<person> p )
    {
        auto proxy = std::dynamic_pointer_cast<person_proxy>(p) ;
        return std::dynamic_pointer_cast<T>( proxy ? proxy->actual : p ) ;
    }

    template< typename T, typename... ARGS >
	static std::shared_ptr<person_proxy> make( ARGS&&... args )
    { return std::make_shared<person_proxy>( std::make_shared<T>( std::forward<ARGS>(args)... ) ) ; }

    template < typename T >
    void convert( std::string new_name = "" ) { rebind( actual->convert<T>(new_name) ) ; }
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
	std::string mala_colour = "red", buddhist_rank = "monk";
  public:
    using person_impl::person_impl ;
    virtual std::string faith() const override { return "buddhist" ; }

	std::string get_mala_colour() const {return mala_colour;}
	void set_mala_colour (const std::string& colour) {mala_colour = colour;}
	std::string get_buddhist_rank() const {return buddhist_rank;}
	void set_buddhist_rank (const std::string& rank) {buddhist_rank = rank;}
	template <typename T>
	void reincarnates() {std::cout << name() << " has reincarnated to a " << typeid(T).name() << ".\n" ;}
};

struct dog {};

int main()
{
    std::shared_ptr<person_proxy> priya = person_proxy::make<buddhist>( "Priya", 28 ) ;
    std::shared_ptr<person_proxy> sandy = person_proxy::make<wasp>( "Sandy", 23, priya ) ;
    priya->befriend(sandy) ;
    sandy->print() ;

    auto sandy_best_friend = person_proxy::cast<buddhist>( sandy->best_friend() ) ;
    if(sandy_best_friend)
    {
	    std::cout << sandy_best_friend->name() << ", a " << sandy_best_friend->faith() << ", is wearing a "
	                   << sandy_best_friend->get_mala_colour() << " mala on her wrist.\n" ;
	    sandy_best_friend->set_mala_colour ("gold");
	    std::cout << sandy_best_friend->name() << "'s mala is now " << sandy_best_friend->get_mala_colour() << ".\n";
	    const std::string old_rank = sandy_best_friend->get_buddhist_rank();
	    sandy_best_friend->set_buddhist_rank ("Dalai Lama");
	    std::cout << sandy_best_friend->name() << "'s rank has changed from " << old_rank << " to " <<
	    	sandy_best_friend->get_buddhist_rank() << "." << std::endl;
	    sandy_best_friend->reincarnates<dog>();
    }
}

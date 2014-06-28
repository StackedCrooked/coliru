#include <iostream>
#include <string>
#include <typeinfo>
#include <memory>

struct person
{
    struct visitor { virtual ~visitor() = default ; } ;

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

    virtual bool accept( person::visitor& ) = 0 ;
	bool accept( person::visitor&& v ) { return accept(v) ; } // forward to virtual
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

        template < typename T > std::shared_ptr<person_impl> convert ( std::string new_name ) {
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
	virtual bool accept( person::visitor& v ) override { return actual->accept(v) ; }

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
    \
    struct visitor { virtual ~visitor() = default ; virtual bool visit( denomination* ) = 0 ; }; \
    virtual bool accept( person::visitor& pv ) override \
    { auto v = dynamic_cast<visitor*>(&pv) ;  return v ? v->visit(this) : false ; } \
};

DEFINE_PERSON(wasp)
DEFINE_PERSON(muslim)
DEFINE_PERSON(agnostic)

template < typename T > struct counting_visitor : person::visitor, T::visitor
{
    virtual bool visit( T* ) override { return ++cnt ; }
    operator int() const { return cnt ; }
    int cnt = 0 ;
};

int main()
{
    auto mary = person_proxy::make<wasp>( "Mary", 28 ) ;
    auto sandy = person_proxy::make<wasp>( "Sandy", 23, mary ) ;
    mary->befriend(sandy) ;
    auto fatima = person_proxy::make<muslim>( "Fatima", 20, sandy ) ;
    auto agnes = person_proxy::make<wasp>( "agnes", 24, fatima ) ;
    auto shazia = person_proxy::make<muslim>( "Shazia", 24, agnes ) ;
    std::shared_ptr<person> persons[] = { mary, sandy, fatima, agnes, shazia,
                                          person_proxy::make<agnostic>( "Agnes", 22 ),
                                          person_proxy::make<wasp>( "Lilly", 26 ) } ;

    struct a_new_polymorphic_operation : person::visitor, wasp::visitor, muslim::visitor, agnostic::visitor
    {
        virtual bool visit( wasp* w ) override
        { std::cout << w->name() << ": implementation for wasps\n" ; return true ; }
        virtual bool visit( muslim* m ) override
        { std::cout << m->name() << ": implementation for muslims\n" ; return true ; }
        virtual bool visit( agnostic* a ) override
        { std::cout << a->name() << ": implementation for agnostics\n" ; return true ; }
    };
    for( auto& p : persons ) p->accept( a_new_polymorphic_operation{} ) ;
    std::cout << "--------------------------\n" ;

    counting_visitor<wasp> wasp_counter ;
    for( auto& p : persons ) p->accept(wasp_counter) ;
    std::cout << "#wasps: " << wasp_counter << '\n' ;
    std::cout << "--------------------------\n" ;

    struct print_sabbath_visitor : person::visitor, wasp::visitor, muslim::visitor // ignore agnostics
    {
        virtual bool visit( wasp* w ) override { std::cout << w->name() << ": Sunday\n" ; return true ; }
        virtual bool visit( muslim* m ) override { std::cout << m->name() << ": Friday\n" ; return true ; }
    };
    for( auto& p : persons ) p->accept( print_sabbath_visitor{} ) ;
}

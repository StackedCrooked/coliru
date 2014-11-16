#include <iostream>
#include <string>
#include <map>
#include <list>
#include <functional>

struct person ;

struct publisher
{
    void publish_obituary( person* deceased ) { for( auto fn : subscribers ) fn(deceased) ; }

    using list_type = std::list< std::function< void( person* ) > > ;
    class token { list_type::iterator iter ; token( list_type::iterator iter ) : iter(iter) {} friend struct publisher ; };

    template < typename FN >
    token subscribe( FN&& fn ) { return subscribers.emplace( subscribers.end(), std::forward<FN>(fn) ) ; }

    void unsubscribe( token tok ) { subscribers.erase( tok.iter ) ; }

    private: list_type subscribers ;
};


struct person {

    enum relation_type { ENEMY, PROSPECTIVE_EMPLOYER, SECRET_CRUSH, AQUAINTANCE, MENTOR };

    explicit person( const std::string& n ) : name(n), token( announcer.subscribe( std::bind( &person::handle_death, this, std::placeholders::_1 ) ) ) {}
    ~person() { announcer.unsubscribe(token) ; }

    std::multimap< person*, relation_type > related_persons ;
    void add_relation( person* who, relation_type what ) { if(who) related_persons.emplace(who,what) ; }

    void handle_death( person* who ) {

        if( who != this ) {
    	    const auto n = related_persons.erase(who) ;
    	    if(n) {
                std::clog << name << ": removed '" << who->name << "' from " ;
    	        if(n>1) std::clog << n << " relations\n" ;
    	        else std::clog << "one relation\n" ;
    	    }
        }
    }

	void dies() { dead = true ; announcer.publish_obituary(this) ; }

	static publisher announcer ;

    std::string name;
    const publisher::token token ;
    private: bool dead = false ;
};

publisher person::announcer ;

int main() {
    
    const auto coroner = [] ( person* who, char begins_with, const char* name ) {
                                 if( !who->name.empty() && who->name[0] == begins_with )
                                     std::clog << "coroner '" << name << "' certifies " << who->name << "'s death.\n" ; };
                                     
    person::announcer.subscribe( std::bind( coroner, std::placeholders::_1, 'B', "Svetlana" ) ) ;
    person::announcer.subscribe( std::bind( coroner, std::placeholders::_1, 'M', "Eliyahu" ) ) ;
    person::announcer.subscribe( std::bind( coroner, std::placeholders::_1, 'S', "Eliyahu" ) ) ;

    person bob_("Bob"), sam("Sam"), mary("Mary"), kate("Kate");
    auto bob = std::addressof(bob_) ;

    sam.add_relation( bob, person::ENEMY ) ;
    mary.add_relation( bob, person::PROSPECTIVE_EMPLOYER ) ;
    kate.add_relation( bob, person::SECRET_CRUSH ) ;
    sam.add_relation( bob, person::PROSPECTIVE_EMPLOYER ) ;
    sam.add_relation( bob, person::AQUAINTANCE ) ;
    mary.add_relation( bob, person::MENTOR ) ;
    sam.add_relation( std::addressof(mary), person::AQUAINTANCE ) ;

    bob->dies() ;
    std::clog << "--------------\n" ;
    mary.dies() ;
    std::clog << "--------------\n" ;
    sam.dies() ;
}

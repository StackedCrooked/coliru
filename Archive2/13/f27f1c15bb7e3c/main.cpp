#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <list>

struct Person {
    std::string name;
	Person (const std::string& newName) : name(newName) {}
	virtual ~Person() = default;

    virtual bool is( std::string tag ) const { return tag == class_tag() ;  }
	virtual void load( std::istream& stm ) { std::getline( stm, name ) ; }
	virtual void save( std::ostream& stm ) const { stm << class_tag() << '\n' ; do_save_(stm) ; }

	static std::unique_ptr<Person> create( std::istream& stm ) ;

	protected:
        virtual void do_save_( std::ostream& stm ) const { stm << name << '\n' ; }
	    struct exemplar {} ; Person( exemplar ) ; // only for creating prototypical objects
	    Person() = default ;

	private:
	    static Person prototype ;
        virtual std::string class_tag() const { return "Person" ; }
        virtual Person* do_create( std::istream& stm ) {
            auto p = new Person ;
            p->load(stm) ;
            return p ;
        }
};

Person Person::prototype{ exemplar{} } ;

namespace {
    constexpr std::size_t MAX_CLASSES = 2048 ;
    std::size_t n_classes = 0 ;
    Person* exemplars[MAX_CLASSES] {} ; // forms a chain of responsibility
}

Person::Person( Person::exemplar ) : name( "protype object" ) { exemplars[n_classes++] = this ; }

std::unique_ptr<Person> Person::create( std::istream& stm ) {
     std::string tag ;
     while( std::getline( stm, tag ) && tag.empty() ) ;
     for( std::size_t i = 0 ; i < n_classes ; ++i ) {
         if( exemplars[i]->is(tag) ) return std::unique_ptr<Person>( exemplars[i]->do_create(stm) ) ;
     }

     return nullptr ;
}

struct Guy : Person {
    int coolness;
    Guy (const std::string& name, int a) : Person(name), coolness(a) {}

    virtual void load( std::istream& stm ) override {
        Person::load(stm) ;
        stm >> coolness >> std::skipws ;
    }
    virtual void save( std::ostream& stm ) const { stm << class_tag() << '\n' ; do_save_(stm) ; }

    protected:
        virtual void do_save_( std::ostream& stm ) const override {
            Person::do_save_(stm) ;
            stm << coolness << '\n' ;
        }

        Guy( exemplar e ) : Person(e) {};
	    Guy() = default ;

    private:
        static Guy prototype ;
        virtual std::string class_tag() const override { return "Guy" ; }
        virtual Person* do_create( std::istream& stm ) override {
            auto p = new Guy ;
            p->load(stm) ;
            return p ;
        }
};

Guy Guy::prototype{ exemplar{} } ;

struct Girl : Person {
    int beauty, cupsize;
    Girl (const std::string& name, int a, int b) : Person(name), beauty(a), cupsize(b) {}

    virtual void load( std::istream& stm ) override {
        Person::load(stm) ;
        stm >> beauty >> cupsize >> std::skipws ;
    }
    virtual void save( std::ostream& stm ) const { stm << class_tag() << '\n' ; do_save_(stm) ;}

    protected:
        virtual void do_save_( std::ostream& stm ) const override {
            Person::do_save_(stm) ;
            stm << beauty << ' ' << cupsize << '\n' ;
        }

        Girl( exemplar e ) : Person(e) {};
	    Girl() = default ;

    private:
        static Girl prototype ;
        virtual std::string class_tag() const override { return "Girl" ; }
        virtual Person* do_create( std::istream& stm ) override {
            auto p = new Girl ;
            p->load(stm) ;
            return p ;
        }
};

Girl Girl::prototype{ exemplar{} } ;

struct Boxer : Guy  {
    int punchingStrength, numKnockouts;
    Boxer (const std::string& name, int a, int b, int c)
        : Guy(name, a), punchingStrength(b), numKnockouts(c) {}

    virtual void load( std::istream& stm ) override {
        Guy::load(stm) ;
        stm >> punchingStrength >> numKnockouts >> std::skipws ;
    }
    virtual void save( std::ostream& stm ) const { stm << class_tag() << '\n' ; do_save_(stm) ;}

    protected:
        virtual void do_save_( std::ostream& stm ) const override {
            Guy::do_save_(stm) ;
            stm << punchingStrength << ' ' << numKnockouts << '\n' ;
        }

        Boxer( exemplar e ) : Guy(e) {};
	    Boxer() = default ;

    private:
        static Boxer prototype ;
        virtual std::string class_tag() const override { return "Boxer" ; }
        virtual Person* do_create( std::istream& stm ) override {
            auto p = new Boxer ;
            p->load(stm) ;
            return p ;
        }
};

Boxer Boxer::prototype{ exemplar{} } ;

struct Cheerleader : Girl {
	int cheeringLoudness, batonSkill;
	Cheerleader (const std::string& name, int a, int b, int c, int d) : Girl(name, a, b),
		cheeringLoudness(c), batonSkill(d) {}

	virtual void load( std::istream& stm ) override {
	    Girl::load(stm) ;
	    stm >> cheeringLoudness >> batonSkill >> std::skipws ;
	}
	virtual void save( std::ostream& stm ) const { stm << class_tag() << '\n' ; do_save_(stm) ;}

	protected:
	    virtual void do_save_( std::ostream& stm ) const override {
            Girl::do_save_(stm) ;
            stm << cheeringLoudness << ' ' << batonSkill << '\n' ;
        }

        Cheerleader( exemplar e ) : Girl(e) {};
	    Cheerleader() = default ;

	private:
        static Cheerleader prototype ;
        virtual std::string class_tag() const override { return "Cheerleader" ; }
        virtual Person* do_create( std::istream& stm ) override {
            auto p = new Cheerleader ;
            p->load(stm) ;
            return p ;
        }
};

Cheerleader Cheerleader::prototype{ exemplar{} } ;

int main() {
    const char* const path = "people.txt" ;

    {
        std::list<Person*> people { new Guy( "John Doe", 5 ),
                                     new Cheerleader( "Mary May", 1, 2, 3, 4 ),
                                     new Boxer( "Rocky Balboa", 7, 8, 9 ),
                                     new Girl( "Madame Yes", 10, 11 ) } ;
        std::ofstream file(path) ;
        for( auto p : people ) { p->save(file) ; file << '\n' ; delete p ; }
    }
    // std::cout << "----- file contains: -------\n" << std::ifstream(path).rdbuf() ;
    {
        std::list< std::unique_ptr<Person> > people ;
        std::ifstream file( "people.txt" ) ;

        while(true) {
             auto p = Person::create(file) ;
             if(p) people.push_back( std::move(p) ) ;
             else break ;
        }

        // std::cout << "----- created from file: -------\n" ;
        for( auto& p : people ) p->save( std::cout << '\n' ) ;
    }
}

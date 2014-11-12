#include <iostream>
#include <list>

struct Person { 
    struct visitor { virtual ~visitor() = default ; };
    virtual ~Person() = default ;
	virtual void accept( visitor* ) = 0;
};

struct Athlete : public virtual Person {
    
    struct visitor 
    {
        virtual ~visitor() = default ;
        virtual void visit( Athlete* ) = 0 ;
    };
    
	virtual void accept( Person::visitor* ov ) override 
    {
        auto av = dynamic_cast<Athlete::visitor*>(ov) ;
        if(av) av->visit(this) ; 
    }
};

struct Singer : public virtual Person {
    
    struct visitor 
    {
        virtual ~visitor() = default ;
        virtual void visit( Singer* ) = 0 ;
    };
    
    virtual void accept( Person::visitor* ov ) override 
    {
        auto sv = dynamic_cast<Singer::visitor*>(ov) ;
        if(sv) sv->visit(this) ; 
    }
};

struct SingingAthlete : public Athlete, public Singer {
    
    struct visitor 
    {
        virtual ~visitor() = default ;
        virtual void visit( SingingAthlete* ) = 0 ;
    };
    
    virtual void accept( Person::visitor* ov ) override 
    {
        auto sav = dynamic_cast<SingingAthlete::visitor*>(ov) ;
        
        if(sav) sav->visit(this) ; // if visitor implements SingingAthlete::visitor
        
        else // visit both Athlete::visitor and Singer::visitor
        {
            Athlete::accept(ov) ;
            Singer::accept(ov) ;
        }
    }
};

int main() {
    
    struct RunningShoes : Person::visitor, Athlete::visitor, Singer::visitor {
        virtual void visit( Athlete* ) override 
        { std::cout << "Athlete puts on the running shoes.\n" ; }
    	virtual void visit( Singer* ) override 
        { std::cout << "Singer has no need for the running shoes.\n" ; }
    };
    
    struct Microphone: Person::visitor, Athlete::visitor, Singer::visitor {
    	virtual void visit( Athlete*) override 
        { std::cout << "Athlete has no need for the microphone.\n" ; }
    	virtual void visit( Singer* ) override 
        { std::cout << "Singer sings with the microphone.\n" ; }
    };
    
    struct KaraokeWalkman : Person::visitor, SingingAthlete::visitor {
        virtual void visit( SingingAthlete* ) override 
        { std::cout << "SingingAthlete jogs with the KaraokeWalkman.\n" ; }
    };

    Person::visitor* objects[] = { new RunningShoes,  new Microphone, new KaraokeWalkman };
    std::list<Person*> people = { new Athlete, new Singer, new SingingAthlete };

    for( Person* x: people )
    {
        for( auto object : objects ) x->accept(object) ;
        std::cout << '\n' ;
    }
}
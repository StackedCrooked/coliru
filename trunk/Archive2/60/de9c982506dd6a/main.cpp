#include <iostream>

struct solid
{
    virtual ~solid() {}
    virtual bool collide( const solid& ) const { return false ; }
};

struct projectile : solid { /* ... */ };
struct enemy : solid { /* ... */ };
struct wall : solid { /* ... */ };

struct player : public solid
{
    virtual bool collide( const solid& other ) const override
    {
        if( const projectile* p = dynamic_cast< const projectile* >(&other) )
            return collide( *p ) ;

        if( const enemy* e = dynamic_cast< const enemy* >(&other) )
            return collide( *e ) ;

        if( const wall* w = dynamic_cast< const wall* >(&other) )
            return collide( *w ) ;

        return solid::collide(other) ;
    }

    private:
        virtual bool collide( const projectile& ) const
        { return std::cout << "player::collide(projectile)\n" ; }

        virtual bool collide( const enemy& ) const
        { return std::cout << "player::collide(enemy)\n" ; }

        virtual bool collide( const wall& ) const
        { return std::cout << "player::collide(wall)\n" ; }
};

int main ()
{
    projectile proj ;
    enemy e ;
    wall w ;
    const solid* objects[] = { &e, &w, &proj } ;

    player p ;
    for( const solid* s : objects ) p.collide(*s) ;

}

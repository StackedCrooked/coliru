#include <iostream>
#include <list>

struct Weapon ;
struct Missile ;
struct Armour ;

struct inventory_visitor { // Visitor
    virtual ~inventory_visitor() = default ;
    virtual void visit( const Weapon* ) = 0 ;
	virtual void visit( const Missile* ) = 0  ;
	virtual void visit( const Armour* ) = 0 ;
};

struct InventoryItem {
	virtual ~InventoryItem() = default ;
	virtual void accept( inventory_visitor& visitor ) const = 0;
};

template < typename DERIVED > struct InventoryItem_impl : InventoryItem { // CRTP
	virtual void accept( inventory_visitor& visitor ) const override {
	    visitor.visit( dynamic_cast<const DERIVED*>(this) ) ;
	}
};

struct Weapon: InventoryItem_impl<Weapon> {} ;
struct Missile: InventoryItem_impl<Missile> {} ;
struct Armour: InventoryItem_impl<Armour> {} ;

struct Menu : inventory_visitor
{
    virtual void visit( const Weapon* ) override { std::cout << "Menu::insert weapon\n" ; }
    virtual void visit( const Missile* ) override { std::cout << "Menu::insert missile\n" ; }
    virtual void visit( const Armour* ) override { std::cout << "Menu::insert armor\n"; }
} ;

struct ListBox : inventory_visitor
{
    virtual void visit( const Weapon* ) override { std::cout << "ListBox::append weapon\n" ; }
    virtual void visit( const Missile* ) override { std::cout << "ListBox::append missile\n" ; }
    virtual void visit( const Armour* ) override { std::cout << "ListBox::append armor\n"; }
} ;

struct Arsenal : inventory_visitor
{
    virtual void visit( const Weapon* ) override { std::cout << "Arsenal::store weapon\n" ; }
    virtual void visit( const Missile* ) override { std::cout << "Arsenal::store missile\n" ; }
    virtual void visit( const Armour* ) override { std::cout << "Arsenal::store armor\n"; }
} ;

int main() {

    Menu menu ;
    ListBox lb ;
    Arsenal a ;

	std::list<Weapon*> weapons = {new Weapon, new Weapon };
	std::list<Armour*> armours = {new Armour, new Armour };
	std::list<Missile*> missiles = {new Missile, new Missile, new Missile };

	for( auto p : weapons ) { p->accept(menu) ; p->accept(lb) ; p->accept(a) ; }
	std::cout << '\n' ;

	for( auto p : armours ) { p->accept(menu) ; p->accept(lb) ; p->accept(a) ; }
	std::cout << '\n' ;

	for( auto p : missiles ) { p->accept(menu) ; p->accept(lb) ; p->accept(a) ; }
}

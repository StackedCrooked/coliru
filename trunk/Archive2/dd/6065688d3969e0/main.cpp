#include <iostream>
#include <iomanip>
#include <type_traits>
 
using namespace std;
 
class IMoveable
{
    string m_str;
public:
	IMoveable( string str ): m_str( str ) {}
	~IMoveable() {}
	IMoveable( IMoveable&& m ): m_str( move( m.m_str ) ) { cout << "Moved " << m_str << "\n"; }
	IMoveable( const IMoveable& m ): m_str( m.m_str ) { cout << "Copied " << m_str << "\n"; }
};
 
class IBase_nodef {
public:
	virtual ~IBase_nodef() {}
};
 
class IBase {
public:
	virtual ~IBase() {}
	IBase() = default;
	IBase( const IBase& ) = default;
	IBase( IBase&& ) = default;
	IBase& operator=( const IBase& ) = default;
	IBase& operator=( IBase&& ) = default;
};
 
class IBase_nodestructor {
};
 
class TMy_nodef: public IBase_nodef {
	IMoveable m;
public:
	TMy_nodef( string str ): m( str ) {}
};
 
class TMy: public IBase {
	IMoveable m;
public:
	TMy( string str ): m( str ) {}
};
 
class TMy_nodestructor: public IBase_nodestructor {
	IMoveable m;
public:
	TMy_nodestructor( string str ) : m( str ) {}
};
 
template <class T, class Y>
void print_info() {
	cout << boolalpha;
	cout << setw( 32 ) << left << "is_copy_assignable"                << setw( 8 ) << is_copy_assignable<T>::value              << setw( 8 ) << is_copy_assignable<Y>::value << '\n';
	cout << setw( 32 ) << left << "is_copy_constructible"             << setw( 8 ) << is_copy_constructible<T>::value           << setw( 8 ) << is_copy_constructible<Y>::value << '\n';
	cout << setw( 32 ) << left << "is_move_assignable"                << setw( 8 ) << is_move_assignable<T>::value              << setw( 8 ) << is_move_assignable<Y>::value << '\n';
	cout << setw( 32 ) << left << "is_move_constructible"             << setw( 8 ) << is_move_constructible<T>::value           << setw( 8 ) << is_move_constructible<Y>::value << '\n';
	cout << setw( 32 ) << left << "is_nothrow_copy_assignable"        << setw( 8 ) << is_nothrow_copy_assignable<T>::value      << setw( 8 ) << is_nothrow_copy_assignable<Y>::value << '\n';
	cout << setw( 32 ) << left << "is_nothrow_copy_constructible"     << setw( 8 ) << is_nothrow_copy_constructible<T>::value   << setw( 8 ) << is_nothrow_copy_constructible<Y>::value << '\n';
	cout << setw( 32 ) << left << "is_nothrow_move_assignable"        << setw( 8 ) << is_nothrow_move_assignable<T>::value      << setw( 8 ) << is_nothrow_move_assignable<Y>::value << '\n';
	cout << setw( 32 ) << left << "is_nothrow_move_constructible"     << setw( 8 ) << is_nothrow_move_constructible<T>::value   << setw( 8 ) << is_nothrow_move_constructible<Y>::value << '\n';
	cout << setw( 32 ) << left << "is_polymorphic"                    << setw( 8 ) << is_polymorphic<T>::value                  << setw( 8 ) << is_polymorphic<Y>::value << '\n';
	cout << setw( 32 ) << left << "is_destructible"                   << setw( 8 ) << is_destructible<T>::value                 << setw( 8 ) << is_destructible<Y>::value << '\n';
	cout << setw( 32 ) << left << "has_virtual_destructor"            << setw( 8 ) << has_virtual_destructor<T>::value          << setw( 8 ) << has_virtual_destructor<Y>::value << '\n';
	cout << setw( 32 ) << left << "is_trivial"                        << setw( 8 ) << is_trivial<T>::value                      << setw( 8 ) << is_trivial<Y>::value << '\n';
	cout << setw( 32 ) << left << "is_trivially_destructible"         << setw( 8 ) << is_trivially_destructible<T>::value       << setw( 8 ) << is_trivially_destructible<Y>::value << '\n';
	cout << setw( 32 ) << left << "has_trivial_copy_assign"           << setw( 8 ) << has_trivial_copy_assign<T>::value         << setw( 8 ) << has_trivial_copy_assign<Y>::value << '\n';
	cout << setw( 32 ) << left << "has_trivial_copy_constructor"      << setw( 8 ) << has_trivial_copy_constructor<T>::value    << setw( 8 ) << has_trivial_copy_constructor<Y>::value << '\n';
	cout << setw( 32 ) << left << "has_trivial_default_constructor"   << setw( 8 ) << has_trivial_default_constructor<T>::value << setw( 8 ) << has_trivial_default_constructor<Y>::value << '\n';
}
 
#define PRINT_INFO(T, Y) \
	cout << #T << " vs " << #Y << endl; \
	print_info<T, Y>(); \
	cout << endl;
 
int main()
{
	TMy_nodef my_nodef( TMy_nodef( "TMy_nodef" ) );
	TMy my( TMy( "TMy" ) );
	TMy_nodestructor my_nodestructor( TMy_nodestructor( "TMy_nodestructor" ) );
	cout << endl;
	PRINT_INFO( IBase_nodef, IBase );
	PRINT_INFO( TMy_nodef, TMy );
	PRINT_INFO( IBase_nodestructor, TMy_nodestructor );
	return 0;
}
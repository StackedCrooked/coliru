// Cplus project, interfaces for data flow.
// copyright David Krauss, created 7/23/13

#ifndef CPLUS_STAGE_H
#define CPLUS_STAGE_H

#include "util.h"

#include <typeindex>
#include <fstream>
#include <memory> // For unique_ptr owning configs.
#include <map>

namespace cplus {

struct passed_exception : std::logic_error { passed_exception() : std::logic_error( "ICE: Failed to stop exception propagation after normal handling." ) {} };

enum class pass_policy { mandatory, optional, enable_if };
enum class diagnose_policy { none, pass, fatal }; // Apply to either sender or receiver. Sender cannot specify none.

void finalize( util::poor_conversion ) {} // fallback overload, worse than derived-to-base conversion
void next_stage( util::poor_conversion );

namespace impl {
    template< typename sig, typename = void >
	struct is_callable : std::false_type {};
	
	template< typename ftor, typename ... arg >
	struct is_callable< ftor( arg ... ), decltype(void( std::declval< ftor & >() ( std::declval< arg >() ... ) )) > : std::true_type {};
	
	template< typename base, typename v > // GCC workaround: usual trait definition style produces strange, inconsistent results.
	constexpr bool is_passable_fn( ... ) { static_assert ( sizeof (base) > 0, "Pass to incomplete type." ); return false; }
	
	template< typename base, typename v >
	constexpr typename std::enable_if< std::is_void< decltype ( next_stage( std::declval< base & >() ).template pass< pass_policy::enable_if >( std::declval< v >() ) ) >::value, bool >::type
	is_passable_fn( int ) { return true; }
	
	template< typename base, typename v, typename q = void >
	struct is_passable : std::integral_constant< bool, is_passable_fn< base, v >(0) > {};
	
	template< typename base, typename v >
	struct is_passable< base, v, decltype( next_stage( std::declval< base & >() ).template pass< pass_policy::enable_if >( std::declval< v && >() ) ) > : std::true_type {};
}

// Adaptor for deriving one stage from another and using base's output iterator.
template< typename base_type, typename ... config_types >
class derived_stage : public base_type {
	std::tuple< config_types const & ... > configs;
	friend derived_stage & next_stage( derived_stage & o ) { return o; }
	
	void operator () () = delete; // pass() is a requirement for communication up the stack.
	
	template< typename t >
	typename std::enable_if< ! std::is_base_of< std::exception, typename std::decay< t >::type >::value >::type
	pass_or_diagnose( t && o ) { pass( std::forward< t >( o ) ); }
	
	template< typename t > // Virtual-dispatch to a surrogate error receiver when none is implemented.
	typename std::enable_if< std::is_base_of< std::exception, typename std::decay< t >::type >::value >::type
	pass_or_diagnose( t && o ) { diagnose< diagnose_policy::pass, t >( true, std::forward< t >( o ) ); }
	
	template< typename t >
	typename std::enable_if< impl::is_passable< base_type, t >::value >::type
	bypass( t && o ) { next_stage( static_cast< base_type & >( * this ) ).pass( std::forward< t >( o ) ); }
	
	struct tag {};
	
public:
	typedef base_type base;
	typedef derived_stage stage;
	
	void flush() {}
	
	template< typename ... args >
	derived_stage( args && ... a ) : derived_stage( tag(), std::tuple<>(), std::forward< args >( a ) ... ) {}
	
	template< typename ... acc_config, typename in_config, typename ... args > // if next argument is the next config object
	derived_stage( typename std::enable_if< sizeof ... ( acc_config ) != sizeof ... ( config_types )
			&& std::is_convertible< in_config, typename util::tuple_element< sizeof ... ( acc_config ), decltype( configs ) >::type >::value, tag >::type,
		std::tuple< acc_config ... > && cacc, in_config && c, args && ... a )
		: derived_stage( tag(), std::tuple_cat( std::move( cacc ), std::forward_as_tuple( std::forward< in_config >( c ) ) ), std::forward< args >( a ) ... ) {}
	
	template< typename ... acc_config, typename in_config, typename ... args > // if next argument isn't the next config object
	derived_stage( typename std::enable_if< sizeof ... ( acc_config ) != sizeof ... ( config_types )
			&& ! std::is_convertible< in_config, typename util::tuple_element< sizeof ... ( acc_config ), decltype( configs ) >::type >::value, tag >::type,
		std::tuple< acc_config ... > && cacc, in_config && c, args && ... a )
		: derived_stage( tag(), std::tuple_cat( std::move( cacc ), std::make_tuple( util::make_implicit_thunk(
			std::bind( & base::template get_config< typename std::tuple_element< sizeof ... ( acc_config ), std::tuple< config_types const ... > >::type >, this ) ) ) ),
			std::forward< in_config >( c ), std::forward< args >( a ) ... ) {}

	template< typename ... acc_config, typename ... args > // if configuration is complete
	derived_stage( typename std::enable_if< sizeof ... ( acc_config ) == sizeof ... ( config_types ), tag >::type,
		std::tuple< acc_config ... > && cacc, args && ... a )
		: base( std::forward< args >( a ) ... ), configs( std::move( cacc ) ) {}
	
	template< typename client = typename std::tuple_element< 0, std::tuple< config_types const ..., void > >::type >
	typename std::enable_if< util::tuple_index< client &, decltype( configs ) >::value != ( sizeof ... ( config_types ) ), client & >::type
	get_config() { return std::get< util::tuple_index< client &, decltype( configs ) >::value >( configs ); }
	
	template< typename client >
	typename std::enable_if< util::tuple_index< client &, decltype( configs ) >::value == ( sizeof ... ( config_types ) ),
		decltype( std::declval< base >().template get_config< client >() ) >::type
	get_config() { return base::template get_config< client >(); }
	
	template< pass_policy policy = pass_policy::mandatory >
	static typename std::enable_if< policy != pass_policy::enable_if >::type // to see overload resolution errors, specify enable_if.
	pass( util::poor_conversion ) { static_assert( policy == pass_policy::optional, "invalid pass argument" ); }
	
	template< pass_policy policy = pass_policy::mandatory, typename arg >
	typename std::enable_if< impl::is_callable< base_type( arg ) >::value >::type
	pass( arg && a ) & // Pass to immediate superclass.
		try { this->base_type::operator () ( std::forward< arg >( a ) ); }
		catch ( passed_exception & ) {}
	
	template< pass_policy = pass_policy::mandatory, typename arg >
	typename std::enable_if< impl::is_callable< base_type( arg, void(*)() ) >::value && impl::is_passable< base_type, arg >::value >::type
	pass( arg && a ) & // Pass to immediate superclass with a functor representing the rest of the stack.
		try { this->base_type::operator () ( std::forward< arg >( a ), [&] { this->bypass( std::forward< arg >( a ) ); } ); }
		catch ( passed_exception & ) {}
	
	template< pass_policy policy = pass_policy::mandatory, typename arg >
	typename std::enable_if< ! impl::is_callable< base_type( arg ) >::value && ! impl::is_callable< base_type( arg, void(*)() ) >::value && impl::is_passable< base_type, arg >::value >::type
	pass( arg && a ) & // Pass to derived_stage recursive base.
		{ bypass( std::forward< arg >( a ) ); }
	
	template< pass_policy policy = pass_policy::mandatory, typename arg >
	typename std::enable_if< policy != pass_policy::enable_if || impl::is_callable< base_type( arg ) >::value || impl::is_passable< base_type, arg >::value >::type
	pass( arg && a ) && {
		pass< policy >( std::forward< arg >( a ) );
		finalize( * this );
	}
	
	template< pass_policy policy = pass_policy::mandatory, typename iter >
	typename std::enable_if< policy != pass_policy::enable_if || impl::is_callable< base_type( typename std::iterator_traits< iter >::reference ) >::value
							|| impl::is_passable< base_type, typename std::iterator_traits< iter >::reference >::value >::type
	pass( iter first, iter last ) &
		{ for ( ; first != last; ++ first ) pass< policy >( * first ); }
	
	template< pass_policy policy = pass_policy::mandatory, typename iter >
	typename std::enable_if< policy != pass_policy::enable_if || impl::is_callable< base_type( typename std::iterator_traits< iter >::reference ) >::value
							|| impl::is_passable< base_type, typename std::iterator_traits< iter >::reference >::value >::type
	pass( iter first, iter last ) && {
		pass< policy >( first, last );
		finalize( * this );
	}
	
	template< typename ... t >
	util::function< void( t ) ... > pass_function()
		{ return { std::bind( static_cast< void (derived_stage::*) ( t ) >( & derived_stage::pass_or_diagnose ), this, std::placeholders::_1 ) ... }; }
	
	template< diagnose_policy policy, typename exception_type, typename ... args >
	typename std::enable_if< impl::is_passable< stage, exception_type >::value, bool >::type
	diagnose( bool condition, args && ... a ) {
		if ( condition ) {
			pass< pass_policy::mandatory >( exception_type( std::forward< args >( a ) ... ) );
			if ( policy == diagnose_policy::fatal ) throw passed_exception();
		}
		return condition;
	}
	
	/*template< diagnose_policy policy, typename exception_type, typename ... args >
	typename std::enable_if< ! impl::is_passable< stage, exception_type >::value, bool >::type
	diagnose( bool condition, args && ... a ) {
		if ( condition ) throw exception_type( std::forward< args >( a ) ... );
		return false;
	}*/
};

namespace impl {
	template< typename t, typename = void >
	struct strip_derived_stage { typedef t type; };
	// Remove derived_stage interface from output types to simplify making *this coincide with a specialization from pile().
	template< typename t >
	struct strip_derived_stage< derived_stage< t > & > { typedef t & type; };
	template< typename t >
	struct strip_derived_stage< derived_stage< t > > { typedef t type; };
}

// Non-virtual abstract base class.
template< typename output_type >
struct stage_base {
	output_type cont;
	
	friend decltype( next_stage( std::declval< output_type & >() ) )
	next_stage( stage_base & o ) { return next_stage( o.cont ); }
	
	template< typename ... args >
	stage_base( args && ... a ) : cont( std::forward< args >( a ) ... ) {}
	
	template< typename ... arg >
	typename std::enable_if< impl::is_callable< output_type & ( arg ... ) >::value >::type
	operator () ( arg && ... a )
		{ cont( std::forward< arg >( a ) ... ); }
	
	template< typename client >
	decltype( std::declval< output_type & >().template get_config< client >() )
	get_config() { return cont.template get_config< client >(); }
};

template< typename base, typename ... config >
derived_stage< base, config ... > &
next_stage( derived_stage< base, config ... > & o ) { return o; }

template< typename output >
typename output::stage &
next_stage( stage_base< output > & o ) { return next_stage( o.cont ); }

template< typename output, typename ... config_types >
using stage = derived_stage< stage_base< output >, config_types ... >;

template< typename s >
typename std::enable_if< ! std::is_same< typename s::base, typename s::stage_base >::value >::type
finalize( s &o ) {
	try {
		o.flush();
	} catch ( passed_exception & ) {}
	finalize( static_cast< typename s::base & >( o ) );
}

/*	Each pipeline step chains to finalize for the next one. When an iterator without
	finalize is reached, synchronization stops. That iterator should be the last. */
template< typename s >
typename std::enable_if< std::is_same< typename s::base, typename s::stage_base >::value >::type
finalize( s &o ) {
	try {
		o.flush();
	} catch ( passed_exception & ) {}
	if ( ! std::is_reference< decltype( o.cont ) >::value ) finalize( o.cont ); // Only finalizing rvalues would be more consistent, but error-prone.
}

// Stage parameterization and pragma distribution.
struct config_base : util::abc {
	config_base() = default;
	config_base( config_base const & ) = delete;
};

template< typename output_iterator >
class config_manager : public stage< output_iterator > {
protected:
	std::map< std::type_index, std::unique_ptr< config_base > > registry;
public:
	template< typename config_ret_type >
	config_ret_type &get_config() {
		typedef typename std::remove_const< config_ret_type >::type config_type;
		auto entry = registry.find( typeid( config_type ) );
		if ( entry == registry.end() ) {
			entry = registry.insert( std::make_pair( std::type_index( typeid( config_type ) ), std::unique_ptr< config_base >( new config_type() ) ) ).first; // config struct gets value initialized
		}
		return static_cast< config_type & >( * entry->second );
	}
	
	template< typename ... args >
	config_manager( args && ... a )
		: config_manager::stage( std::forward< args >( a ) ... ) {}
};

template< typename cont, template< typename ... > class ... stages >
struct stack_stages;

template< typename cont >
struct stack_stages< cont >
	{ typedef typename impl::strip_derived_stage< cont >::type type; };

template< typename cont, template< typename ... > class stage, template< typename ... > class ... rem >
struct stack_stages< cont, stage, rem ... >
	{ typedef stage< typename stack_stages< cont, rem ... >::type > type; };

template< template< typename ... > class ... stages, typename ... args >
derived_stage< typename stack_stages< typename std::tuple_element< sizeof ... ( args ) - 1, std::tuple< args ... > >::type, stages ... >::type >
pile( args && ... a )
	{ return { std::forward< args >( a ) ... }; }

}

#endif

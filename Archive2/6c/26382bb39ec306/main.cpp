#include <iostream>
#include <type_traits>
#include <tuple>
#include <utility>

void breaking( ) {
    std::cout << "Nice!~\n";
}

template<typename T, typename TFx>
table& set_function( std::true_type, T&& key, TFx&& fx ) {
    typedef typename std::decay<TFx>::type clean_fx;
    std::string fkey( key );
    lua_CFunction freefunc = &detail::lua_cfun;
    auto hint = funcs.find( fkey );
    detail::lua_func* target = nullptr;
    if ( hint == funcs.end( ) ) {
	    std::shared_ptr<detail::lua_func> sptr( new detail::lambda_lua_func<clean_fx>( std::forward<TFx>( fx ) ) );
	    hint = funcs.emplace_hint( hint, fkey, std::move( sptr ) );
    }
    target = hint->second.get( );
    (*target)( state( ) );
}

int main () {
    
    something( breaking );
    
}
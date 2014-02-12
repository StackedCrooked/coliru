#define strip(...) __VA_ARGS__
#define define_function(A, B, C) template< strip A > struct B ## _impl;

define_function( (class X, class Y), foo, bar )
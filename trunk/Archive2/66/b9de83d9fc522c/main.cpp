#include <iostream>

// Quiz: how to define a macro that can "remember" the name passed to the previous call? (Using void for the first.)
#define REGISTER_TYPE(Name) struct Name { /* previous_type */ };


REGISTER_TYPE(X) // should generate: struct X { typedef void previous_type; };
REGISTER_TYPE(Y) // should generate: struct Y { typedef X previous_type; };
REGISTER_TYPE(Z) // should generate: struct Z { typedef Y previous_type; };


// verify if previous_type is generated
static_assert(std::is_same<X::previous_type, void>::value, "");
static_assert(std::is_same<Y::previous_type, X>::value, "");
static_assert(std::is_same<Z::previous_type, Y>::value, "");


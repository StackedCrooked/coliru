#include <iostream>
#include <utility>

#include <boost/preprocessor.hpp>

#define DECLARE_VARS(z, n, text) text##n = 30 - n

#define PRED(r, state)\
    BOOST_PP_NOT_EQUAL(state, 30)

#define OP(r, state)\
	BOOST_PP_INC(state)


#define OUTER_LOOP(r, state)\
	BOOST_PP_FOR(1, PRED, OP, INNER_LOOP)

#define INNER_LOOP(r, state)\
	if (BOOST_PP_CAT(i, BOOST_PP_DEC(state)) > i##state) {\
		std::swap(BOOST_PP_CAT(i, BOOST_PP_DEC(state)), i##state);\
	}

#define PRINT(r, state)\
	std::cout << i##state << ' ';

int main() {
	int BOOST_PP_ENUM(30, DECLARE_VARS, i);

	BOOST_PP_FOR(0, PRED, OP, PRINT)
	std::cout << '\n';

	BOOST_PP_FOR(0, PRED, OP, OUTER_LOOP)
	
	BOOST_PP_FOR(0, PRED, OP, PRINT)
}
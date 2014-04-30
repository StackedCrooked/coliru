#define FE_1(WHAT, X) WHAT(X) 
#define FE_2(WHAT, X, ...) WHAT(X)FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT(X)FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT(X)FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT(X)FE_4(WHAT, __VA_ARGS__)
//... repeat as needed

#define GET_MACRO(_1,_2,_3,_4,_5,NAME,...) NAME 
#define FOR_EACH(action,...) \
  GET_MACRO(__VA_ARGS__,FE_5,FE_4,FE_3,FE_2,FE_1)(action,__VA_ARGS__)

#define REGISTER_ENUM_VALUE(X) E_##X,
#define REGISTER_ENUM(...) enum X { FOR_EACH(REGISTER_ENUM_VALUE, __VA_ARGS__) }
#define REGISTER_CLASS(X) ; class X {}
#define REGISTER(...) REGISTER_ENUM(__VA_ARGS__) FOR_EACH(REGISTER_CLASS, __VA_ARGS__)

REGISTER(A, B, C);

#define QUOTE_E(x) # x
#define QUOTE(x) QUOTE_E(x)

#define N 123

char const * str = "hello world = " QUOTE(N) ""; 

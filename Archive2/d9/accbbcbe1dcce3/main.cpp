#define elifdef elif defined 

#define Stuff

#ifdef Nope
//
#elifdef Stuff
int main() {}
#endif
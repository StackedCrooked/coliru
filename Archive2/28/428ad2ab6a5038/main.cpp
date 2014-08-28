#include <map>
#include <iostream>

std::map<const void *,const char *> mapping;
void * foo(const void *) { std::cout << "Called 'foo'\n"; return nullptr;}
extern void * bar(const void *,const char *);

// Uncommenting the function below gets rid of the warning -- perhaps because
// the code optimizes to where it is clear that there is no reason for the
// warning.  It also demonstrates that the function is called from 'main' with
// properly initialized second argument.  With function commented out, a bogus
// warning is produced (and, of course, the program does not link).
#if 0
void * bar(const void *, const char * s)
{
    std::cout << "Called 'bar' with s=" << (s ? s : "<NULL>") << '\n';
	return nullptr;
}
#endif

const void *
snafu(const void * param, const bool flag)
{
  mapping.insert(std::make_pair(nullptr,"initialized"));
  const char * thing;
  if (!flag) {
  	#if 0
  	// Activating this branch prevents the warning.
  	thing = "whatever";
  	#else
  	// Bogus warning if this branch is present.
    thing = mapping.at(param);
    #endif
    if (nullptr == thing) {
      throw "FUBAR";
    } 
  }

  const void * mapped = mapping.at(param);
  const void * result = flag ? foo(mapped): bar(mapped, thing);
  return (result);
}

int main()
{
	snafu(nullptr,false);
	snafu(nullptr,true);
	return 0;
}

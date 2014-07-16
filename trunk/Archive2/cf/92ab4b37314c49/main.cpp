#include <string>
struct base { virtual std::string g() = 0; };
std::string f(base&& arg) { return arg.g(); }
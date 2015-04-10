#include <string>

using namespace std;

string make_plural(string &word, size_t c, const string &ending = "s")
  {
     return c > 1 ? word + ending : word;
  }
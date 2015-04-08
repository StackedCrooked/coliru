#include <string>

class string_t :
  private std::basic_string<char>
{
public:
   string_t() :
      basic_string<value_type>() {}

   string_t(
      const basic_string<value_type>& s) :
         basic_string<value_type>(s) {}

   virtual ~string_t() {}
};

int main () {
    string_t s;
}
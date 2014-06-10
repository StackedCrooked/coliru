#include <map>
#include <exception>
#include <sstream>
#include <iostream>
using std::endl;
using std::logic_error;
using std::string;
using std::stringstream;

template<char const*... Args_t>
struct Finder {

   Finder() {
      Add<Args_t...>();
      m_len = sizeof...(Args_t);
      m_count = 0;
   }

   void Append(char const* key, string val) {
       Found_t::iterator found = m_founds.find(key);
       if (found == m_founds.end()) return; // irrelevant
       if (!found->second.empty()) {
           stringstream str;
           str << "Found an already existing key: [" << key << ']' << endl;
           throw logic_error(str.str());
       }
       found ->second = std::move(val);
       ++m_count;
   }
   bool Complete() { return m_len == m_count; }

private:
   struct dummy{};
   template<typename, char const*... Ar_t> 
   struct Add_struct;

   template<typename T, char const* First_t, char const*... Rest_t> 
   struct Add_struct<T, First_t, Rest_t...> {
       Finder *this_;
       void operator()() const {
           this_->m_founds.insert(Found_t::value_type(First_t, ""));
           Add_struct<T,Rest_t...>{this_}();
       }
   };

   template<typename T> 
   struct Add_struct<T> {
       Finder *this_;
       void operator()() const {}
   };

   template<char const* First_t, char const*... Rest_t> void Add() {
       m_founds.insert(Found_t::value_type(First_t, ""));
       Add_struct<dummy,Rest_t...>{this}();
   }
   
   typedef std::map<char const*, string> Found_t;
   Found_t m_founds;
   int m_len;
   int m_count;

};
static constexpr char const s_first[] = "first";
static constexpr char const s_second[] = "second";
int main() {
    Finder<s_first, s_second> finder;
}

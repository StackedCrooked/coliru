#include <string>
#include <memory>
#include <boost/serialization/strong_typedef.hpp>

typedef std::string FirstName_t;
typedef std::string SecondName_t;

struct Panda
{
   FirstName_t FirstName;
   SecondName_t SecondName;
};


template<typename T>
struct firstname_alloc : std::allocator<T> { };

template<typename T>
struct secondname_alloc : std::allocator<T> { };


struct Panda_Adv_1
{
   std::basic_string<char, std::char_traits<char>, firstname_alloc<char> > FirstName;
   std::basic_string<char, std::char_traits<char>, secondname_alloc<char> > SecondName;
};


BOOST_STRONG_TYPEDEF(std::string, FirstName_bt)
BOOST_STRONG_TYPEDEF(std::string, SecondName_bt)

struct Panda_Adv_2
{
    FirstName_bt FirstName;
    SecondName_bt SecondName;
};



int main(){

   Panda p1 = {"Yuan_Zai", "Ha"};
   p1.FirstName = p1.SecondName;

/* Won't Compile due to no implicit type conversion between
 * std::basic_string<char, std::char_traits<char>, firstname_alloc<char> >
 * std::basic_string<char, std::char_traits<char>, secondname_alloc<char> >
   Panda_Adv_1 p2 = {"Yuan_Zai", "Ha"};
   p2.FirstName = p2.SecondName;
*/

/* Won't compile due to the same reason, but using
 * Boost's strong_typedef
   Panda_Adv_2 p3 = {"Yuan_Zai", "Ha"};
   p3.FirstName = p3.SecondName;
*/
}

#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
using namespace std;
using namespace boost;

int main ()
{
    locale::generator gen;
	std::locale utf8Loc(gen(""));
    string str1(" яhelloй world! ");
    str1 = locale::to_upper(str1, utf8Loc);
    trim(str1);

    string str2 =
		locale::to_lower(
			ireplace_first_copy(str1,"hello","goodbye"), 
			utf8Loc
		);
    cout << str1 << "   "  << str2 <<endl;
}
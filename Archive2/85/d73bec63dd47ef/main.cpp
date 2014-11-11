#include <iostream>
#include <iterator>
#include <cstring>
#include <algorithm>
#include <stdexcept>

template <std::size_t N,
          std::size_t N2>
std::string extractQualifiedName(char const(&str)[N], char const(&name)[N2])
{
    using namespace std;
	static_assert(N >= N2, "");

	// Argument to isalnum must be unsigned:
	auto cond = [] (unsigned char c) {return !isalnum(c) && c != '_';};

	char const* iter = str;
	for (;;++iter)
	{
		iter = search( iter, end(str),
		               begin(name), end(name)-1 );

		if (iter == end(str))
			throw invalid_argument("");

		if ((iter == begin(str)      || cond(iter[-1]))
		 && (iter ==   end(str) - N2 || cond(iter[N2-1])))
			break;
	}

	return string(find_if(reverse_iterator<char const*>(iter),
	                      reverse_iterator<char const*>(str),
	                      [=] (char c) {return cond(c) && !strchr(":(){} ", c);}).base(),
	              iter + N2-1);
}


namespace foo {
namespace {

template<int i>
int (*bar(int (*arg)(int *)))(int *)
{
	std::cout << extractQualifiedName(__PRETTY_FUNCTION__, __func__);
	return arg;
}

} // anonymous namespace
} // namespace foo

int main()
{
	foo::bar<1337>(nullptr);
}

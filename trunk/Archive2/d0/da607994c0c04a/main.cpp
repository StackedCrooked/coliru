#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <cstring>

template <typename InputIterator, typename T>
InputIterator findClosing( InputIterator first, InputIterator last, T close )
{
    if (first == last)
		return last;

	auto open = *first;
	unsigned counter = 1;
	while (++first != last)
	{
		if (*first == close && --counter == 0)
			return first;
		if (*first == open)
			++counter;
	}

	return last;
}

template <std::size_t N,
          std::size_t N2>
std::string f(char const(&str)[N], char const(&name)[N2])
{
	using namespace std;

	// Argument to isalnum must be unsigned:
	auto cond = [] (unsigned char c) {return !isalnum(c) && c != '_';};

	auto iter = str;
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

	auto origin_iter = iter;
	while(iter != begin(str))
	{
		--iter;
		for (auto p : {"()", "{}"})
		if (*iter == p[1])
			iter = findClosing(reverse_iterator<char const*>(iter+1),
			                   reverse_iterator<char const*>(begin(str)),
			                   p[0]).base()-2;

		if (cond(*iter) && *iter != ':')
			return string(iter+1, origin_iter+N2-1);
	}

	return string(iter, origin_iter+N2-1);
}
constexpr bool isNotIdentifierChar(const char *pf)
{
    return !((*pf>='0' && *pf<='9') || (*pf>='a' && *pf<='z') || (*pf>='A' && *pf<='Z') || *pf=='_');
}

constexpr const char* getNamespaceEnd(const char *pf, const char *func)
{
    return (isNotIdentifierChar(pf) && 0==strncmp(&pf[1], func, strlen(func))
        && isNotIdentifierChar(pf+strlen(func)+1) && ':'!=pf[strlen(func)+1]) 
        ? &pf[1] 
        : getNamespaceEnd(++pf, func);
}

constexpr const char* getNamespaceStartIter(const char *pf, const char *end)
{
    return (*pf==' ' && (nullptr==strchr(&pf[1],' ') || strchr(&pf[1], ' ') > end)) 
        ? &pf[1] 
        : getNamespaceStartIter(++pf, end);
}

constexpr const char* getNamespaceStart(const char *pf, const char *func)
{
    return getNamespaceStartIter(pf, getNamespaceEnd(pf, func));
}

constexpr size_t getNamespaceSize(const char *pf, const char *func)
{
    return getNamespaceEnd(pf, func) - getNamespaceStart(pf, func);
}

class NamespaceString {
public:
    NamespaceString(const char *pf, const char *func) 
        : start(getNamespaceStart(pf, func)),
          end(getNamespaceEnd(pf, func)),
          endfunc(end+strlen(func))
        {}
    std::string getString() const {
        return std::string(start, end);
    }
    std::string getStringWithFunction() const {
        return std::string(start, endfunc);
    }
private:
    const char *start;
    const char *end;
    const char *endfunc;
};

namespace bar {
namespace foo {
namespace {

template<int i>
int (*bar(int (*arg)(int *)))(int *)
{
	std::cout 
        << "PRETTY: " << __PRETTY_FUNCTION__ << '\n'
        << "func:   " << __func__ << '\n'
        << "Columbo:" << f(__PRETTY_FUNCTION__, __func__) << '\n'
        << "Edward: " << NamespaceString(__PRETTY_FUNCTION__, __func__).getStringWithFunction() << '\n';

	return arg;
}

void foobar()
{
	std::cout 
        << "PRETTY: " << __PRETTY_FUNCTION__ << '\n'
        << "func:   " << __func__ << '\n'
        << "Columbo:" << f(__PRETTY_FUNCTION__, __func__) << '\n'
        << "Edward: " << NamespaceString(__PRETTY_FUNCTION__, __func__).getStringWithFunction() << '\n'
        ;
}

} // anonymous namespace
} // namespace foo
}

int main()
{
	bar::foo::bar<1337>(nullptr);
	bar::foo::foobar();
}

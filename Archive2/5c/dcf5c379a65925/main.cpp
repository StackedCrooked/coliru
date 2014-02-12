#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <iterator>
#include <type_traits>

using namespace std;

template <typename Foo>
struct Gizmo
{
    Foo mF;
	Gizmo (Foo f) : mF (f) {};

	template <typename Iter>
    typename enable_if<is_convertible<typename iterator_traits<Iter>::value_type,string>::value>::type
    DoIt(Iter begin, Iter end) const
	{
		stringstream ss;
		ss << "(" << this->mF << ")\n";
		const std::string s = ss.str();
		copy (begin, end, ostream_iterator <std::string> (cout, s.c_str()));
	}
};

int main()
{
	list <string> l;
	l.push_back ("Hello");
	l.push_back ("world");
	
	Gizmo <unsigned> g (42);
	g.DoIt (l.begin(), l.end());
    
    const char* const char_pointers[] = {"foo", "bar", "baz"};
    g.DoIt (begin(char_pointers), end(char_pointers));
    
    typedef int battelship;
    vector<battleship> armada{1,2,3,4};
    g.DoIt (begin(armada), end(armada));
}

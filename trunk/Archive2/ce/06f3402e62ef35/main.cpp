#include <thread>
#include <utility>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

namespace py
{
    struct split
    {
		vector<string> operator()(const char * text)
		{
			stringstream ss	{ text };
			vector<string> v;
			string word;
			while (ss>>word)
			{
				v.emplace_back(word);
			}
			return move(v);
		}
	};
	
	struct join
	{
		join(char x) : m_sep(x){}

		template<typename... Args>
		string operator()(Args&&... args)
		{
			vector<string> liste {std::forward<Args>(args)...};
			stringstream ss;
			for (const auto& s : liste)
			{
				ss << s << m_sep;;
			}
			return ss.str();
		}

		string operator()(const vector<string>&& elements)
		{
			stringstream ss;
			for (const auto& e : elements)
			{
				ss << e << m_sep;
			}
			return ss.str();
		}
		char m_sep;
	};
}

inline auto operator"" _join (char x) -> py::join
{
	py::join j(x);
	return j;
}

inline auto operator"" _split (const char * text, long unsigned int l) ->  vector<string>
{
	py::split j;
	return move(j(text));
}

inline vector<string> sorted (const vector<string>& v)
{
	vector<string> r(v);
	sort(r.begin(), r.end(), less<string>());
	return move(r);
}


int main(int, char* argv[])
{
	// print(' '.join(sorted('python is cool'.split(), key=len)))
	const auto Xend = ' '_join(sorted("python is cool and c++11 as well"_split));
	cout << Xend << endl;

#if 0
	const auto x1 = ' '_join("abc","def","...","xyz");
	const auto x2 = "split me baby"_split;
	const auto x3 = '_'_join("split me baby"_split);
	const auto x4 = sorted(x2);
#endif

	return 0;
}

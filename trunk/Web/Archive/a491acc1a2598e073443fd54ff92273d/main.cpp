#include <cassert>
#include <iostream>
#include <string>
#include <vector>


std::string extract(const std::string & input, char delim, char escape)
{
    enum class State
	{
		parsing,
		escaped
	};

	State state = State::parsing;

	std::string found = "";
	std::string parsed = "";

	for (auto && c : input)
	{
		if (state == State::parsing)
		{
			if (c == delim)
			{
				found.append(parsed);
				parsed.clear();
			}
			else if (c == escape)
			{
				state = State::escaped;
			}
			else
			{
				parsed += c;
			}
		}
		else
		{
			assert(state == State::escaped);
			parsed += c;
			state = State::parsing;
		}
	}

	if (!parsed.empty())
	{
		found.append(parsed);
	}

	return found;
}


int main()
{
	std::cout << extract("tab	bat", '\t', '\\') << std::endl;
}


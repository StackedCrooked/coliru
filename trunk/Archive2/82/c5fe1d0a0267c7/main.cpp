#include <set>
#include <vector>

int main()
{
    std::vector<int> v;

    for(auto& i : v)
    {
		i = 2;
	}

    std::set<int> s;

    for(auto& j : s)
	{
		j = 2;
	}
	
	return 0;
}
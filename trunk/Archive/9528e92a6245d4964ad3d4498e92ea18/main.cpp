#include <stdio.h>

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

void tfnc()
{
   std::vector<int> v = {11, 22, 33, 44};

    std::set<std::pair<int,int> > twoOutOf4;

	do {
	
		twoOutOf4.insert( std::make_pair(std::min(v[0], v[1]), std::max(v[0], v[1])));
	
	} while(std::next_permutation(v.begin(), v.end()));
	
	for(auto & i: twoOutOf4) {
		printf("%d %d ", i.first, i.second);
		printf("\n");
	}
}

int main()
{
   tfnc();
}
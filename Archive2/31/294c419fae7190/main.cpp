#include <iostream>
#include <string>
#include <vector>

std::map <int, vector<pair<int, int>> > ::iterator it1 = Kcom2.begin();
    std::map<std::pair< int, int>, int> ::iterator it2 = PairSupp.begin();
	std::map< vector<pair<int, int> >, int> TotalSub;

	int i = 0;

	while (it1 != Kcom2.end())
	{
		vector< pair<int, int> > temp = Kcom2[i];
		vector< pair<int, int> > ::iterator it3 = temp.begin();

		while (it3 != temp.end())
		{
			
			while (it2 != PairSupp.end())
			{
				
				//auto itt = PairSupp.find(it3);
				//++TotalSub[it3].insert(it2->second);

				if (it3 == it2->first)
					++TotalSub[it3].insert(it2->second);
				else
					++it2;
			}
			++it3;
			++i;
		}
		++it1;
	}







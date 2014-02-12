

std::map <int, vector<pair<int, int>> > ::iterator it1 = Kcom.begin();
    std::map<std::pair< int, int>, int> ::iterator it2 = Mymap.begin();
	std::map< vector<pair<int, int> >, int> TotalSub;

	int i = 0;

	while (it1 != Kcom.end())
	{
		vector< pair<int, int> > temp = Kcom[i];
		vector< pair<int, int> > ::iterator it3 = temp.begin();

		while (it3 != temp.end())
		{
			
			while (it2 != Mymap.end())
			{
				
				//auto itt = Mymap.find(it3);
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







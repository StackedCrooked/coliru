int ind = 0;
for (const auto& p1 : MyMap2)
{
    AssociatedItem[p1.first.first].push_back(p1.first.second);
	AssociatedItem[p1.first.second].push_back(p1.first.first);

}
void print(list<int> l,int first, int z, int indx)
{
	
	for (list<int>::iterator it = l.begin(); it != l.end(); ++it)
	{
		cout << *it ;
		
		MyMap1[indx].push_back(std::make_pair(first, *it));
			
	    // MyMap1[indx].push_back(*it);  

		 
	}
	cout << endl;
}


void subset(int j, int subset_size, int k, int index)
{

	if (k == 0)
	{
		cout << sp->first << " ==> "  ;
		print(lt[j], sp->first ,  AssociatedItem[sp->first].size(), ind);
		++ind;
		return;
	}
		

	for (int i = index; i < subset_size; ++i)
	{					
		lt[j].push_back(sp->second[i]);
		subset(j, subset_size, k-1, i + 1);
		lt[j].pop_back();
	}

}

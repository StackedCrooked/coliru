// comb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <stdio.h>
#include<list>
#include<map>
#include<vector>
using namespace std;

void print(std::map <int, vector <int> > &Kcom){
	for (std::map <int, vector <int> >::iterator it = Kcom.begin(); it != Kcom.end(); ++it)
	//	cout << " " << it;
	cout << endl;
}

void subset(std::map <int, vector <int> >& AssociatedItem, int subset_size, int k, int index, std::map <int, vector <int> > &Kcom){
	int j = 0;
	for (const auto& p1 : AssociatedItem)
	{

		if (k == 0){
			print(Kcom);
			return;
		}
		for (int i = index; i < AssociatedItem[p1.first].size(); i++){
			Kcom[j].push_back(p1.second[i]);
			++j;
			subset(AssociatedItem, AssociatedItem[p1.first].size(), k - 1, i + 1, Kcom);
			Kcom[j].pop_back();
		}
	}
}

int main()
{
	std::map <int, vector <int> > AssociatedItem;

	AssociatedItem.insert (1,( 3, 4));
	AssociatedItem.insert(2, (3, 4));
	AssociatedItem.insert(3, (1,2, 5));
	AssociatedItem.insert(4, (1,2,3,5));
	AssociatedItem.insert(5, (1));

	std::map <int, vector <int> > Kcom;

	int k = 3;
	int subset_size;
	subset(AssociatedItem, subset_size, k, 0, Kcom);

	system("PAUSE");
	return 0;
}




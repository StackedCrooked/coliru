#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

int main()
{      
    typedef std::vector<std::string> Filetype;
	Filetype myDoc, insertpoint,slice;

	Filetype::iterator itx = std::find(myDoc.begin(), myDoc.end(), *(--insertpoint.end()));
	++itx;
	myDoc.insert(itx, slice.begin(), slice.end());
    std::cout << "DONE";
}

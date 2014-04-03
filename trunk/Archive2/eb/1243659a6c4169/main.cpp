#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;
 
int main()
{
    vector<int> intl;
	copy(istream_iterator<int>(cin),istream_iterator<int>(),back_inserter(intl));
	sort(intl.begin(),intl.end());
	unique_copy(intl.begin(),intl.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
}
#include <iostream>
#include <cstring>

using namespace std;

string convert (string inp) {
    char number[] = "";
	int j = 0;
	int n = inp.length();
	
	for (int i = 0; i < n ; i++){				
		if (isdigit (inp[i]) || inp[i] == ','){ 
			number[j] = inp[i];					
			j++;
		}
	} 
	return number;
}
 
int main()
{
string dig;
string slovo = "<![CDATA[111773,2]]>";
dig = convert (slovo);
cout << "Digital = " << dig;
cin.get();
	return 0;
}
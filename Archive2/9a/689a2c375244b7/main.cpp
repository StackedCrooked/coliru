#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
 
int main()
{
string str, str_qt, str_code, str_price, tmp;

int pos(0), pos_1(0), pos_2(0), count(0);
int len(0), begin(0), end(0), k(0);

struct store {
    string qt;
	string code;
	string price;
};

store *item = new store [500];

ifstream fin("price.mxl");

if (!fin)
	{
		cout<<"File gmp_price.mxl not found";
		cin.get();
		return -1;
	}
	
while(!fin.eof())
{
	getline(fin, str);
	pos = str.find("{16,39,");
	pos_1 = str.find("{16,40,");
	pos_2 = str.find("{16,41,");
	
	if (!pos){
		getline(fin, tmp);
		getline(fin, str_qt);
		len = str_qt.length();
		for (int i(0); i <= len; i++){
			if (str_qt[i]=='\"')
				count++;
			if (count == 2) 
				begin = i;
			if (count == 3)
				end = i;			
		}
		if (count > 2){
			item[k].qt = str_qt.substr(begin+2, end-begin-1);
			}else{
			item[k].qt = '0';
			}
		begin = 0; end = 0; count= 0; k++;
	}	
	if (!pos_1){
		getline(fin, tmp);
		getline(fin, str_code);
		len = str_code.length();
		for (int i(0); i <= len; i++){
			if (str_code[i]=='\"')
				count++;
			if (count == 2) 
				begin = i;
			if (count == 3)
				end = i;
		}
		item[k].code = str_code.substr(begin+2, end-begin-1);
		begin = 0; end = 0; count= 0; k++;
	}	
	if (!pos_2){
		getline(fin, tmp);
		getline(fin, str_price);
		len = str_price.length();
		for (int i(0); i <= len; i++){
			if (str_price[i]=='\"')
				count++;
			if (count == 2) 
				begin = i;
			if (count == 3)
				end = i;
		}
		item[k].price = str_price.substr(begin+2, end-begin-1);
		begin = 0; end = 0; count= 0; k++;
	}
}
cin.get();
fin.close();

// убрать пробел в цене
for (int j = 0; j < k; j++)
		item[j].price.erase(item[j].price.find(' '), 1);

ofstream fout("gmp_price.csv");
	for (int j = 0; j < k; j++)
		fout << item[j].qt << '^' << item[j].code << '^' << item[j].price << endl;
fout.close();

delete [] item;

return 0;
}
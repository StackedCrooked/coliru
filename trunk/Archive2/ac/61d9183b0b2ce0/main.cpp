#include <string>
#include <list>
#include <iostream>
#include <stdint.h>

using namespace std;

void SplitString(const string& path_id,const string& token,list<string>& split_list)
{
    if(path_id.empty())   
		return;	 
  
	int nend=0;   
    int nbegin=0;   
    while(nend != -1)   
    {   
        nend = path_id.find_first_of(token, nbegin);   
        if(nend == -1)   
            split_list.push_back(path_id.substr(nbegin, path_id.length()-nbegin));   
        else  
            split_list.push_back(path_id.substr(nbegin, nend-nbegin));   
        nbegin = nend + 1;   
    }    

}

int main()
{
    string aaa = "/1/2/3/";
    list<string> split_list;
    
    SplitString(aaa,"/",split_list);
    
    for(list<string>::iterator it = split_list.begin();it!=split_list.end();++it)
    {
        cout << *it<<endl;
        cout << "a"<<endl;
    }
    
    return 1;
}
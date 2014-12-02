#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

bool isunique(const string&);
bool onlyspaces(const string&);

int main()
{
   string str;
   cout<<"enter a string";
   cin>>str;

   if(isunique(str))
    cout<<"string is  unique";
   else
    cout<<"string not unique";
}

bool isunique(const string& s)
{
    string temp=s;

    sort(temp.begin(),temp.end());
     auto myiter=unique(temp.begin(),temp.end());

    // if(myiter==s.end())
    if( myiter == temp.end() ) // *************
        return true;
    else
    {
      return onlyspaces( string(myiter,temp.end()) );
    }
}

bool onlyspaces(const string& s)
{
    for(auto i: s)
        if(!isspace(i))
            return false;

        //else // *************
            return true;
}

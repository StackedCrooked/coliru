#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include<iostream> 
using namespace std;




typedef vector<string> vs;

class UserName
{
  public:

    string newMember(vs exist, string newname) { 
        bool found = false;
       bool match = false;
         stringstream ss;
         string result;
            string othername;
        for(int i = 0; i < exist.size(); i++){
            if(exist[i] == newname){
                found = true;
                break;
        }
        }
    if(found){
        for(int x = 1;   ; x++){
                match = false;
                ss.str("");
             ss << newname << x;
                for(int i = 0; i < exist.size();i++){
                    //cout << ss.str() << endl;
                    othername = ss.str();
                    if(exist[i] == othername){
                            match = true;
                            break;
                            }
                    }
                    if(!match){
                     result = ss.str();
                       break;
                }

                    }
                    return result;

                    }
                else return newname;


                }   





};

int main(){

UserName u;

vector<string> Database (4);
    Database.push_back("Justin");
    Database.push_back("Justin1");
    Database.push_back("Justin2");
    Database.push_back("Justin3");



cout << u.newMember(Database, "Justin") << endl;



return 0;
}
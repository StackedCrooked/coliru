#include <iostream>
#include <string>

using namespace std;

string getCommand(void){
  string str="string";
  return str;
}

int main(){
if(getCommand()=="string"){
    std::cout << "something" << std::endl;
	}
return 0;
}
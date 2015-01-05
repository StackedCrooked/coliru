#include <iostream>
#include<map>
using namespace std;
typedef enum  { NODATATYPE = -1, 
            DATATYPEINT, 
            DATATYPEVARCHAR
          } DATATYPE; 
inline string operator+(string str, const DATATYPE dt){
  static map<DATATYPE,string> map;
  if (map.size() == 0){
    #define INSERT_ELEMENT(e) map[e] = #e
            INSERT_ELEMENT(NODATATYPE);     
            INSERT_ELEMENT(DATATYPEINT);     
            INSERT_ELEMENT(DATATYPEVARCHAR);     
    #undef INSERT_ELEMENT
  }   
  return str + map[dt];
}



int main() {
    // your code goes here
	DATATYPE dt1 = DATATYPEINT;
std::string msg = "illegal type for operation" + dt1;
	return 0;
}
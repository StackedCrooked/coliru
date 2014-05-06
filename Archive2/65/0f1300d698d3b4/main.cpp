#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::string error = "Hello's World";
    std::cout << error << std::endl;
    error.erase(std::remove(error.begin(), error.end(), '\''), error.end());
    std::cout << error << std::endl;
    std::string _invocation_id = "abc";
    
                 std::string message_category = "WARNING";
        		 std::string msg_category_query = "";

                  if(message_category == "WARNING")
                          msg_category_query = " ,'WARNING'";
                  else if(message_category == "INFO")
                          msg_category_query = " ,'INFO'";
                  

                  std::string query = std::string("SELECT distinct mp.msg_id, mp.msg_pattern, mp.msg_interpretation, mp.event_type ")
                  + " FROM message_patterns mp  "
                  + " join message_source ms on (mp.msg_id=ms.msg_id)  "
                  + " join message_category mc on (mp.msg_id=ms.msg_id) "
                  + " where ms.invocation_id = '"
                  + _invocation_id
                  + "'"
                  + " and mc.msg_category in ('ERROR' "
                  + msg_category_query
                  + ")";
                  
                  std::cout << query << std::endl;
                  
}



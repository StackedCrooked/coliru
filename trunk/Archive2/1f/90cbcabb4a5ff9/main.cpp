#include <string>
#include <iostream>
 
std::string str_find(std::string start, std::string  end, std::string message);

int main()
{
    std::string a = "invitationtypeSOYSOYname";
 
   /* std::string str_find = "type";
    std::size_t loc = a.find(str_find);
    //std::size_t loc2 = a.find("7")
    loc = loc + str_find.size();
    std::string sub2 = a.substr(loc);
    str_find = "name";
    loc = a.find(str_find);
    std::string sub3 = a.substr(loc);
    sub2.erase(sub2.size()-sub3.size());
    std::cout << sub2 << '\n';
    std::cout << sub3 << '\n';*/
    
    std::string sub_final = str_find("type","name", a);
    std::cout << sub_final << '\n';
}

std::string str_find(std::string start, std::string  end, std::string message)
{
    std::string value;

	//std::string a = "invitationtypeSOYSOYname"; //example
	std::size_t loc = message.find(start);
	loc = loc + start.size();
	std::string sub2 = message.substr(loc);
	loc = message.find(end);
	std::string sub3 = message.substr(loc);
	sub2.erase(sub2.size()-sub3.size());
	return sub2;
}
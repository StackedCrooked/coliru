#include <iostream>
#include <string>
#include <boost/algorithm/string/replace.hpp>



int main(){
    
    std::string text = "Continue on %M for %D and then%C|In %D ]keep right[ on %N| on %T][ in direction %S][ and drive %E]";
    
    std::string condition = "]keep ";
    std::string first = " on %";
    std::string second = " and turn onto %";
    
    size_t pos_to_split = text.find(condition);
    if (pos_to_split == std::string::npos) {
        return -1;
    }
    pos_to_split += condition.length();
    
    std::string text2 = text.substr(0, pos_to_split) + boost::algorithm::replace_all_copy(text.substr(pos_to_split, std::string::npos), first, second);
      
    
    
    std::cout << text << std::endl;
    std::cout << text2 << std::endl;

}
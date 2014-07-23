#include <iostream>
#include <string>

std::string information(const std::string& signature, const int max_depth)
{
    std::string result = "";
    int template_depth = 0;
    for(char c : signature)
    {
        if(c=='<')
            template_depth++;
        if(template_depth <= max_depth)
            result+=c;
        if(c=='>')
            template_depth--;
    }
    return result;
}

std::string getSignature()
{
    return "std::_hash< std::_Umap_traits<std::string, tile::flag_type, std::_Uhash_compare<std::string, std::hash<std::string>, std::equal_to<std::string>, std::allocator<std::pair<const std::string, tile::flag_type>>,false>>::iterator>\
 insert(\n std::_Hash<std::_Umap_traits<std::string, tile::flag_type, std::_Uhash_compare<std::string, std::hash<std::string>, std::equal_to<std::string>>, std::allocator<std::pair<const std::string, tile::flag_type>>, false>>::const_iterator,\n\
 const std::_Hash<std::_Umap_traits<std::string, tile::flag_type, std::_Uhash_compare<std::string, std::hash<std::string>, std::equal_to<std::string>, std::allocator<std::pair<const std::string, tile::flag_type>>, false>>>::value_type &_Val\n)\n";
}

int main()
{
    std::string signature = getSignature();
    for(int depth=0; depth<4; depth++)
        std::cout << information(signature,depth) << std::endl;
}

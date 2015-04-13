#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>

bool typex(std::string& str, std::string t)
{
    if(!str.compare(0, t.length(), t))
    {
        str = str.substr(t.length() + (str.back() == '*'? 0 : 1));
        return true;
    }
    return false;
}

std::string rs_type(std::string& str)
{
    if(typex(str, "void")) return "";
    if(typex(str, "bool")) return "h3d_bool";
    if(typex(str, "int")) return "c_int";
    if(typex(str, "int*")) return "*mut c_int";
    if(typex(str, "float")) return "c_float";
    if(typex(str, "float*")) return "*mut c_float";
    if(typex(str, "const float*")) return "*const c_float";
    if(typex(str, "const char*")) return "*const c_char";
    if(typex(str, "H3DNode")) return "H3DNode";
    if(typex(str, "H3DRes")) return "H3DRes";
    if(typex(str, "H3DOptions::List")) return "H3DOptions";
    if(typex(str, "H3DStats::List")) return "H3DStats";
    
    throw std::runtime_error(std::string("unk type: ") + str);
}

std::string func_name(std::string& str)
{
    auto idx = str.find("(");
    if(idx == str.npos) throw std::runtime_error(std::string("unk func: ") + str);;
    auto result = str.substr(0, idx);
    str = str.substr(idx+1);
    return result;
}

bool func_arg(std::string& str, std::pair<std::string, std::string>& arg)
{
    if(str.front() != ';')
    {
        auto type     = rs_type(str);
        auto paramidx = str.find_first_of(",)");
        auto param    = str.substr(0, paramidx);
        
        str = str.substr(paramidx+1);
        arg = std::make_pair(type, param);
        return true;
    }
    str = "";
    return false;
}

void expect(std::string& str, char c)
{
    if(str.empty() || str.front() != c)
        throw std::runtime_error(std::string("expected ") + c + " but found " + str);
}

std::string conv_func(std::string line)
{
    std::string& text = line;
    
    if(!text.compare(0, 3, "DLL"))
        text = text.substr(4);
        
    std::pair<std::string, std::string> arg;
    std::vector<std::pair<std::string, std::string>> args;
        
    auto ret   = rs_type(text);
    auto fname = func_name(text);
        
    while(func_arg(text, arg))
        args.emplace_back(arg);
        
    std::ostringstream os;
    os << "pub fn " << fname << '(';
    for(auto& arg : args) os << arg.second << ": " << arg.first;
    os << ')';
    if(ret.size()) os << " -> " << ret;
    os << ';';
    return os.str();
}

int main()
{
    std::cout << conv_func("DLL bool h3dHasEmitterFinished(H3DNode emitterNode);") << std::endl;
    
}
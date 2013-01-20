#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include <iostream>


struct MatchExtension
{
    MatchExtension(const std::vector<std::string> & inext) : ext(inext)
    {
        for (auto & e : ext) boost::algorithm::to_lower(e);
    }
    
    bool operator()(std::string path) const
    {
        boost::algorithm::to_lower(path);
        for (const auto & e : ext)
        {
            if (e.size() > path.size())
            {
                continue;
            }
            
            if (!path.compare(path.size() - e.size(), e.size(), e))
            {
                return true;
            }
        }
        return false;
    }
    
    std::vector<std::string> ext;
};


int main()
{
    std::vector<std::string> ext = { "jpg", "jpeg", "png", "bmp" };
    std::vector<std::string> paths = { "1.jpg", "pipo.aaa", "test.png", "2.JPG", "3.JPEG" };
    
    MatchExtension matcher(ext);
    for (auto path : paths)
    {
        std::cout << path << ": " << matcher(path) << std::endl;        
    }
}
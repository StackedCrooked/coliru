#include <algorithm>
#include <string>
#include <iterator>
#include <sstream>
#include <iostream>

int main()
{
        std::string text = "This is a long text word \
                            this word another floor king \
                            queen ace";
 
    std::stringstream ss(text) ;

    std::vector<std::string> vec{ 
                std::istream_iterator<std::string>(ss),
                std::istream_iterator<std::string>() };
                                
    std::vector<std::string> to_find {"word ", "this", 
                          "word", "another", "floor"};                   
    
    std::string aux ="jack";
    
    std::replace_if(   vec.begin( ),vec.end( ),
                    [to_find](const std::string& x)
                    {
                       return std::any_of( 
                              to_find.begin(), 
                              to_find.end(),
                              [x](const std::string& y)
                              { return x == y; }
                                         ) ;
                    },
                    aux );
                    
    text =std::accumulate( vec.begin()+1, vec.end( ), 
                           vec[0],
                         [](std::string s0, std::string const& s1) 
                         { return s0 += " " + s1; }
                        );
    std::cout << text ;
    
}
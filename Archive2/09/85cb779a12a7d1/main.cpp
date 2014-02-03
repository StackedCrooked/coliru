#include <iostream>
#include <string>
#include <sstream>

// return trimmed (leading and trailing spaces removed) string
std::string trim( const std::string& str )
{
    static const std::string ws = " \t\n" ;
    auto first = str.find_first_not_of(ws) ;
    auto last = str.find_last_not_of(ws) ;
    return first == std::string::npos ? "" : str.substr( first, last-first+1 ) ;
}

int main()
{

    const std::string text = "    < baseQueueName >  Hello  < /baseQueueName >  " ;
    std::istringstream stm(text) ;

    std::string left_tag ;
    std::string value ;
    std::string right_tag ;

    // step 1. read the first non whitespace character
    // if text is well formed, the character should be '<'
    char ch ;
    if( stm >> ch && ch == '<' )
    {
        std::cout << "step 1 ok. got: <\n" ;
        // step 2. read everything from there on till a '>' is found
        //         as the tag on the left;  discard the '>'
        // http://www.cplusplus.com/reference/string/string/getline/
        if( std::getline( stm, left_tag, '>' ) )
        {
            std::cout << "step 2 ok. got left_tag: " << left_tag << '\n' ;
            // step 3. read the value uto the next '<', discard the '<'
            if( std::getline( stm, value, '<' ) )
            {
                std::cout << "step 3 ok. got value: " << value << '\n' ;
                // step 4. read and discard the next '/' skipping over white space
                if( stm >> ch && ch == '/')
                {
                    std::cout << "step 4 ok. got: /\n" ;
                    // step 5. read everything from there on till a '>' is found
                    //         as the tag on the right
                    if( std::getline( stm, right_tag, '>' ) && !stm.eof() )
                    {
                        std::cout << "step 5 ok. got right_tag: " << right_tag << '\n' ;

                        // step 6. we have got the raw data now; sanitize it
                        left_tag = trim(left_tag) ;
                        value = trim(value) ;
                        right_tag = trim(right_tag) ;
                        std::cout << "step 6 trim ok.\n\t left tag: " << left_tag
                                  << "\n\tvalue: " << value
                                  << "\n\tright tag: " << right_tag << '\n' ;
                        // step 7. verify that the tags match
                        if( left_tag == right_tag )
                        {
                            std::cout << "step 7 ok. the left and right tags match\n" ;
                            std::cout << "--------------------------\n *** success ***\n"
                                      << "tag: '" << left_tag << "'\n"
                                      << "value: '" << value << "'\n"
                                      << "------------------------\n" ;
                        }
                    }
                }
            }
        }
    }
}

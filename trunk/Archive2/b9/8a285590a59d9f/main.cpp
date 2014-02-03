#include <iostream>
#include <sstream>
#include <string>

void show_get_area_of_stream( std::istringstream& input_stream, const char* desc )
{
    std::cout << "get area " << desc << ": " ;

    // tellg gives us the current get position
    // print out the contents of the string from thereon
    constexpr char quote = '"' ;
    std::cout << quote << input_stream.str().substr( input_stream.tellg() ) << quote << '\n' ;

}

// helper function to consume and validate tags
// skips white space on either side of the tag
// the parameter 'in' has been renamed as 'input_stream' (make intent clear)
// the type of the stream has been changed to a string stream
// (istringstream makes it easy for us to look at the get area of the stream
//  and understand what is going on under the hood; we will leave it as an
// istream (any kind of input stream) in the original code
static bool consume( std::istringstream& input_stream, const char* expected )
{
    std::string str ;

    // what followes is an elaborated version of the original
    // return input_stream >> std::ws >> str >> std::ws && str == expected ;
    // with scaffolding:
    // each step separated out so that it can be viewed on its own,
    // stepped through incrementally in a debugger,
    // and comments annotating what each step does
    // and diagnostic messages printed out after each step to tell us what went on

    show_get_area_of_stream( input_stream, "on entry" ) ;
    std::cout << "expected tag: \"" << expected << "\"\n" ; ;

    // skip leading whitespace
    // (this step is really not essential right now, because  'expected'
    //  is a string that does not contain embedded white spaces)
    bool ok = ( input_stream >> std::ws ).good() ; // ok is false on input failure
    if( !ok ) return false ; // failed, return false (expected tag was not consumed)
    show_get_area_of_stream( input_stream, "after input_stream >> std::ws" ) ;

    // try to read everything upto the next whitespace into str
    ok = ( input_stream >> str ).good() ; // ok is false on input failure
    if( !ok ) return false ; // failed, return false (expected tag was not consumed)
    show_get_area_of_stream( input_stream, "after input_stream >> str" ) ;
    std::cout << "str now contains: \"" << str << "\"\n" ; ;

    // skip trailing whitespaces immediately after the string that was read
    ok = ( input_stream >> std::ws ).good() ; // ok is false on input failure
    if( !ok ) return false ; // failed, return false (expected tag was not consumed)
    show_get_area_of_stream( input_stream, "after another input_stream >> std::ws" ) ;

    std::cout << "actual string read: \"" << str << "\"\n" ; ;
    std::cout << "expected tag: \"" << expected << "\"\n" ; ;

    // if str is the expected tag, we have consumed the expected tag successfully
    bool got_expected_tag = ( str == expected ) ;
    std::cout << "did we get the expected tag? "
               << ( got_expected_tag ? "yes" : "no" ) << '\n' ;

    return got_expected_tag ;
}


int main()
{
    {
        std::istringstream stm( " Title: Alpha Beam With Ernie" ) ;
        bool result = consume( stm, "Title:" ) ;
        std::cout << "consume returned " << std::boolalpha << result << '\n' ;
        show_get_area_of_stream( stm, "after consume( stm, \"Title:\" )" ) ;
    }

    std::cout << "\n---------------------------\n\n" ;

    {
        std::istringstream stm( " Blah: Alpha Beam With Ernie" ) ;
        bool result = consume( stm, "Title:" ) ;
        std::cout << "consume returned " << std::boolalpha << result << '\n' ;
        show_get_area_of_stream( stm, "after consume( stm, \"Title:\" )" ) ;
    }

    std::cout << "\n---------------------------\n\n" ;

    // putting it together now:
    {
        std::istringstream stm( " Title: Alpha Beam With Ernie\n Genre: ...blah..." ) ;
        show_get_area_of_stream( stm, "at start" ) ;

        std::string title ;

        // we already know what goes on inside consume
        // so lets just silence std::cout for the duarion of consume()
        std::cout.clear(std::ios::failbit) ;

        if( consume( stm, "Title:" ) &&
            std::getline( stm, title ) )
        {
            std::cout.clear() ; // unsilence std::cout
            std::cout << "consume() returned true\n"
                       << "std::getline( stm, title ) returned true\n"
                       << "title now contains: \"" << title << "\"\n" ;
            show_get_area_of_stream( stm, "after reading title" ) ;
        }
    }
}

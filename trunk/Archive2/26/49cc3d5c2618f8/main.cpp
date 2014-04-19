#include <iostream>
#include <string>

int main()
{
    const std::wstring strings[] = {  L"12345", L"12345xyz", L"xyz12345", L"123456789012345" } ;
    
    for( auto& wstr : strings ) try
    {
        std::wcout << L"\n'" << wstr << L"' => " ;
        std::size_t pos = 0 ;
        int number = std::stoi( wstr, &pos ) ;
        std::wcout << L"converted to integer " << number << L'\n' ;
        if( pos < wstr.size() ) std::wcout << "    the first " << pos << L" characters were converted\n" ; 
    }
    catch( const std::invalid_argument& ) { std::wcerr << L"no conversion could be performed\n" ; }
    catch( const std::out_of_range& ) { std::wcerr << L"converted value would be out of the range of an int\n" ; }
}


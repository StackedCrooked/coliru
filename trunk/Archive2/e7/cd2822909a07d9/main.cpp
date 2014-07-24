#include <iostream>
#include <iomanip>


std::string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    	output.push_back(' ');
		if( !((i+1) % 16) )
		{
			output.push_back('\n');
		}
    }
    return output;
}



int main ( int argc, char *argv[] )
{

    std::string test;
	int i = 42;
	int j;
    long k = 1023;
    long l;
	
	test.append( (char *)&i, sizeof(int));
	test.append( "[0][1][2][3][4][5][6][7]" );
    test.append( (char *)&k, sizeof(long));

	j = *((int *)(test.substr(0,sizeof(i)).data()));
    l = *((long *)(test.substr(28,sizeof(k)).data()));
	std::cout << string_to_hex( test ) << std::endl;
    std::cout <<  "j = " << j << " l = " << l << std::endl;
	return( 0 );
}
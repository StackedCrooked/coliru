#include <iostream>
#include <vector>
using namespace std;

int const margin    = 2;
int const n         = 16 + margin;      // The code uses an n*n table of characters.

int data_col( int i ) { return i + margin; }
int data_row( int i ) { return i + margin; }

int main()
{
    vector<vector<char>>    lines( n, vector<char>( 2*n, ' ' ) );
    auto const              cells =
        [&]( int const x, int const y ) -> char& { return lines[y][2*x]; };

    for( int i = 0;  i < 16;  ++i )
    {
        static char const hex_digits[] = "0123456789ABCDEF";
        cells( data_col( i ), 0 ) = hex_digits[i];
        cells( 0, data_row( i ) ) = hex_digits[i];
    }

    for( int y = 0;  y < 16;  ++y ) for( int x = 0;  x < 16;  ++x )
    {
        int const c = 16*y + x;
        cells( data_col( x ), data_row( y ) ) = (c < ' '? '-' : char( c ));
    }

    for( int y = 0;  y < n;  ++y )
    {
        cout.write( lines[y].data(), lines[y].size() ) << endl;
    }
}

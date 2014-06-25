#include <iostream>
#include <sstream>
#include <climits>
void get(uint bytes){
    //--- nur Ausgabe ---//
    std::stringstream bits;
    std::stringstream vals;
    //------------------//
    char spacer = ' ';
    uint comparator = 1;
	for(uint i = 0; i < sizeof(bytes) * CHAR_BIT; i++, comparator <<= 1){
        if(comparator & bytes){
            switch(comparator){
                case 1:
                    break;
                case 2:
                    break;
                // ...
                case 32768:
                    break;
                default:
                    // return invalid request exception
                    break;
            }
        }
        //--- nur Ausgabe ---//
        bits << spacer << (i<10?" ":"") << i;
        vals << spacer << " " << !!(comparator & bytes);
        spacer = '|';
        //------------------//
	}
    std::cout << "\n" << bits.str() << "\n" << vals.str();
}
int main()
{
    uint data = 16854135;
    get(data);
}
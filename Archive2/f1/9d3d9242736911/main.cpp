#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

typedef char BYTE;

void shift_1bit_left(vector<BYTE> &array)
{
    if(array.size() == 0) {
		return;
	}
	
    BYTE shifted = 0x00;    
    BYTE overflow = (0x80 & array[0]) >> 1;

    for (int i = (array.size() - 1); i >= 0; i--) {	
        shifted = (array[i] << 1) | overflow;
        overflow = (0x80 & array[i]) >> 1;
        array[i] = shifted;
    }
}

string char_to_hex(unsigned char c) {
  stringstream stream;
  
	stream << setfill('0') << setw(2) << hex << (int)c;
	
	return stream.str();
}


string get_hex_string(const vector<BYTE> &vec) {
 string out;
	
 for(long i = 0; i < vec.size(); i++) {
   out += char_to_hex(vec[i]);
 }
	
 return out;
}

int main() {
	// your code goes here
	
	vector<BYTE> key = {0x1};
	
	for(int i = 0; i < 20; i++) {
		cout << get_hex_string(key) << endl;
		//bit_rotate_left_key(key, 1);
		shift_1bit_left(key);
	}
	
	return 0;
}
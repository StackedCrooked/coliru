#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

typedef char BYTE;

void rotate_1bit_left(vector<BYTE> &array) {
    if(array.size() == 0) {
		return;
	}
	
    BYTE shifted = 0x00;    
    BYTE overflow = (0x80 & array[0]) >> 7;

    for (int i = (array.size() - 1); i >= 0; i--) {	
        shifted = (array[i] << 1) | overflow;
        overflow = (0x80 & array[i]) >> 1;
        array[i] = shifted;
    }
}

void rotate_bits_left(vector<BYTE> &array, unsigned int number_of_bits) {
    for(int i = 0; i < number_of_bits; i++) { 
        rotate_1bit_left(array);
    }
}

string char_to_binary(unsigned char c) {
    string s;
    int x = (int)c;
    
    do
    {
        s.push_back('0' + (x & 1));
    } while (x >>= 1);
    
    while(s.size() < 8) { 
        s = s + '0';
    }
    
    std::reverse(s.begin(), s.end());
    
    return s;
}

string char_to_hex(unsigned char c) {
    stringstream stream;
  
	stream << setfill('0') << setw(2) << hex << (int)c;
	
	return stream.str();
}


string get_hex_string(const vector<BYTE> &vec) {
    string out;
	
    for(int i = 0; i < vec.size(); i++) {
        out += char_to_hex(vec[i]);
    }
	
    return out;
}

string get_binary_string(const vector<BYTE> &vec) {
    string out;
    
    for(int i = 0; i < vec.size(); i++) {
        out += char_to_binary(vec[i]);
    }
	
    return out;
}

int main() {
	// your code goes here
	
	vector<BYTE> key = {0x00, 0x01};
	const int number_of_bits = 20;
    
	for(int i = 0; i < number_of_bits; i++) {
		cout << get_binary_string(key) << endl;
        
		rotate_bits_left(key, 1);
	}
	
	return 0;
}
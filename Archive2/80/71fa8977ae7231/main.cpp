#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdint.h>

using namespace std;


typedef int8_t byte;

int main(int argc, char* argv[])
{
    stringstream sstr2;
    sstr2 << char(0x00);
    sstr2 << char(0x01);
    sstr2 << char(0x02);
    sstr2 << char(0x03);
    sstr2 << char(0x04);
    sstr2 << char(0x05);
    sstr2 << char(0x06);
    sstr2 << char(0x07);
    sstr2 << char(0x08);
    sstr2 << char(0x09);
    sstr2 << char(0xe2);
    sstr2 << char(0x80);
    sstr2 << char(0x08);
    sstr2 << char(0x11);
    sstr2 << char(0x05);
    sstr2 << char(0x05);
    sstr2 << char(0x05);
    sstr2 << char(0x05);
    sstr2 << char(0x05);
    sstr2 << char(0x05);
    sstr2 << char(0x05);
    sstr2 << char(0x05);
    sstr2 << char(0x50);
    sstr2 << char(0x12);
    sstr2 << char(0x13);
    sstr2 << char(0x14);

    char c;
    sstr2 >> c;
    while (sstr2.good()) {
        cout << hex << uppercase << setw(2) << setfill('0') << (int)c;
        sstr2 >> c;
    }
    cout << endl;
}
/************************************************************
* hash.c Rev 0.1
* Generate a logical address filter value from a list of
* Ethernet multicast addresses.
*
* Input:
* User is prompted to enter an Ethernet address in
* Ethernet hex format: First octet entered is the first
* octet to appear on the line. LSB of most
* significant octet is the first bit on the line.
* Octets are separated by blanks.
* After results are printed, user is prompted for
* another address.
*
* (Note that the first octet transmitted is stored in
* the C-LANCE as the least significant byte of the Physical
* Address Register.)
* Output:
* After each address is entered, the program prints the
* hash code for the last address and the cumulative
* address filter function. The filter function is
* printed as 8 hex bytes, least significant byte first.
****************************************************************/
#include <stdio.h>
#include <iostream>
#include <cassert>

using namespace std;

void updateCRC (int bit);
int adr[6], /* Ethernet address */
    ladrf[8], /* Logical address filter */
    CRC[33], /* CRC register, 1 word/bit + extra control bit */
    poly[] = /* CRC polynomial. poly[n] = coefficient of
        the x**n term of the CRC generator polynomial. */
        {    1,1,1,0,1,1,0,1,
            1,0,1,1,1,0,0,0,
            1,0,0,0,0,0,1,1,
            0,0,1,0,0,0,0,0
        };

int main()
{
    int i, byte; /* temporary array indices */
    int hashcode; /* the object of this program */
    for (i=0;i<8;i++) ladrf[i] = 0; /* clear log. adr. filter */

        /* If 1st character = CR, quit, otherwise read address. */
        
    adr[0]=0x4D;
	adr[1]=0x00;
	adr[2]=0x00;
	adr[3]=0x00;
	adr[4]=0x00;
	adr[5]=0x01;
	
    cout << "Address: " << hex << adr[0] << "-" << hex << adr[1] << "-" << hex << adr[2] << 
                    "-" << hex << adr[3] << "-" << hex << adr[4] << "-" << hex << adr[5] << endl;
 		
        
	if ((adr[0] & 1) == 0)
	{ 
		cout << ("First octet of multicast address ");
		cout << ("must be an odd number.\n");
	}
	
	/* Initialize CRC */
	for (i=0; i<32; i++) CRC[i] = 1;
	/* Process each bit of the address in the order of transmission.*/
	for (byte=0; byte<6; byte++)
		for (i=0; i<8; i++)
			updateCRC ((adr[byte] >> i) & 1);
		/* The hash code is the 6 least significant bits of the CRC
			in reverse order: CRC[0] = hash[5], CRC[1] = hash[4], etc.*/
		hashcode = 0;
	for (i=0; i<6; i++) 
		hashcode = (hashcode << 1) + CRC[i];
		/* Bits 3-5 of hashcode point to byte in address filter.
		Bits 0-2 point to bit within that byte. */
	byte = hashcode >> 3;
	ladrf[byte] |= (1 << (hashcode & 7));
	cout << "hashcode (decimal) ladrf[0:63] = " << hashcode << endl;
	for (i=0; i<8; i++)
	cout << hex << ladrf[i];
	cout << (" (LSB first)\n");

	return 0;
}
void updateCRC (int bit)
{
    int j;
    /* shift CRC and control bit (CRC[32]) */
    for (j=32; 	j>0; j--) 
         CRC[j] = CRC[j-1];
    CRC[0] = 0;
    /* If bit XOR (control bit) = 1, set CRC = CRC XOR polynomial. */
    if (bit ^ CRC[32])
        for (j=0; j<32; j++) CRC[j] ^= poly[j];
}
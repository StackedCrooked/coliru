void Init_4bit_tab(unsigned char *dest,unsigned char *source)
        {
            unsigned char masque,i;

            masque=0x08;
            for(i=0; i<4; i++) {
                dest[i] = (*source & masque)>>(3-i);
                masque >>= 1;
            }
        }
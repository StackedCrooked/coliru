struct callbacks
{
short LastFrequency = 9000;
 int *MMIO_RANGE1;
 short Cycle_LN = 65535 / LastFrequency;
 const char *STATUS_FLAGS[5] = // <-- 5 here
 {
   "ACK",
   "NO_VIB",
   "DATA",
   "BYTEPACK",
   "WORDPACK"
 };
}; // <-- ; here

int main() 
{
    
}
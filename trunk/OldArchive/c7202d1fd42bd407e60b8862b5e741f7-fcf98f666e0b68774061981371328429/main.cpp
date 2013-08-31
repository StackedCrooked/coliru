int main() {
    using byte = unsigned char;
    byte* buf = new byte[5];
    for(int i = 0; i < 5; ++i) buf[i] = 0xFF;
    byte mFlag = 0xAD;
    buf[2] |= (byte)(mFlag & 0x7F);
}
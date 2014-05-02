int
MP3Filter::checkBitrate(int nBitrate)
{
    if (nBitRate <= 32) return 32;
    if (nBitRate > 256) return 320;
    static const int realbitrate[256/8] = {
        0, //
        0, //
        0, //
        0, //
        40,  //32-40
        48,  //41-48
        56,  //49-56
        64,  //57-64
        80,  //65-72
        80,  //73-80
        96,  //81-88
        96,  //89-96
        96,  //89-96
        112,  //97-104
        112,  //105-112
        128,  //113-120
        128,  //121-128
        //etc
        };
    return realbitrate[(nBitRate-1)/8];
    // ##########################################
    //if      (nBitrate <= 32)    return 32;
    //else if (nBitrate <= 40)    return 40;
    //else if (nBitrate <= 48)    return 48;
    //else if (nBitrate <= 56)    return 56;
    //else if (nBitrate <= 64)    return 64;
    //else if (nBitrate <= 80)    return 80;
    //else if (nBitrate <= 96)    return 96;
    //else if (nBitrate <= 112)   return 112;
    //else if (nBitrate <= 128)   return 128;
    //else if (nBitrate <= 160)   return 160;
    //else if (nBitrate <= 192)   return 192;
    //else if (nBitrate <= 224)   return 224;
    //else if (nBitrate <= 256)   return 256;
    //return 320;
}
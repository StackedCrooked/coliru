// For each bitfield type:
// #define BITTYPES SEPERATOR(Red) SEPERATOR(Green) SEPERATOR(Blue)
// #define BITNAME color
// #define BITTYPE unsigned __int64 //This is optional. Defaults to unsigned __int64
// #include "FastBitField.inl"

// generates the following class:
// struct colorBitfield {
//     enum colorBitNum {RedBitNum=0, GreenBitNum=1, BlueBitNum=2};
//     enum colorFlag : unsigned __int64 {NoFlags=0, RedFlag=1, GreenFlag=2, BlueFlag=4, AllFlags=-1};
//     union {
//         unsigned __int64 BitField;
//         struct {
//             bool Red : 1;
//             bool Green : 1;
//             bool Blue : 1;
//         };
//     };
//     inline static const _TCHAR* const ToString(colorBitNum color)
//     {
//         switch(color) {
//             case RedBitNum: return _T("Red");
//             case GreenBitNum: return _T("Green");
//             case BlueBitNum: return _T("Blue");
//             default: return 0;
//         }
//     }
// };

// which can be used as follows:
// colorBitfield Pixel;
// Pixel.BitField = 0; // sets all values to zero;
// Pixel.Green = 1; // activates green;
// cout << Pixel.BitField << std::endl;  //this is machine dependant, probably 2. (010 in binary)
// Pixel.BitField |= (colorBitfield::GreenFlag | colorBitfield::BlueFlag); // enables Green and Blue
// cout << (Pixel.BitField & colorBitfield::BlueFlag) << std::endl; // 1, true.

// Notes: Only the first 64 bits are accessable with BitField.
// If you have more than 64 values, BitField only has the first 64.

#ifndef BITTYPES
#error BITTYPES MUST BE DEFINED FOR THIS FILE TO WORK
#endif
#ifndef BITNAME
#error BITNAME MUST BE DEFINED FOR THIS FILE TO WORK
#endif
#ifndef BITTYPE
#define BITTYPE unsigned __int64
#endif

#ifdef SEPERATOR
#define SEPERATORBACKUP SEPERATOR
#undef SEPERATOR
#endif

#define gluehelper(a,b) a ## b
#define glue(a,b) gluehelper(a,b)

#ifdef _UNICODE
#define _T(x) gluehelper(L,x)
#define _TCHAR wchar_t
#else
#define _T(x) x
#define _TCHAR char
#endif

struct glue(BITNAME , Bitfield) {
#define SEPERATOR(x) glue(x,BitNum),
    enum glue(BITNAME,BitNum) {BITTYPES};
#undef SEPERATOR
#define SEPERATOR(x) glue(x,Flag)=1LL<<(glue(x,BitNum)),
    enum glue(BITNAME,Flag) : BITTYPE {NoFlags=0, BITTYPES AllFlags=BITTYPE(-1)};
    union {
        BITTYPE BitField;
        struct {
#undef SEPERATOR
#define SEPERATOR(x) bool x : 1; 
            BITTYPES
        };
    };
    inline static const _TCHAR* const ToString(glue(BITNAME,BitNum) BITNAME)
    {
        switch(BITNAME) {
#undef SEPERATOR
#define SEPERATOR(x) case glue(x,BitNum): return _T(#x);
            BITTYPES;
            default: return 0;
        }
    }
};

#undef SEPERATOR
#ifdef SEPERATORBACKUP
#define SEPERATOR SEPERATORBACKUP
#endif

#undef glue
#undef gluehelper
#undef BITTYPES
#undef BITNAME
#undef BITTYPE
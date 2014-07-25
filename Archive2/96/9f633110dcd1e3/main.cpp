// For each fast bitfield type:
// #define BLOCKTYPES SEPERATOR(Red) SEPERATOR(Green) SEPERATOR(Blue)
// #define BLOCKNAME color
// #define BLOCKTYPE int //This is optional. Defaults to int
// #include "IntBlock.inl"

// generates the following class:
// struct colorBlock {
//     enum colorEnum {colorRed, colorGreen, colorBlue};
//     union {
//         struct {
//             BLOCKTYPE Red;
//             BLOCKTYPE Green;
//             BLOCKTYPE Blue;
//         };
//         BLOCKTYPE Array[3];
//     };
//     
//     inline colorBlock() //These are not initialized for speed.  You can initialize with the other if you want.
//     {}
//     inline colorBlock(BLOCKTYPE _Red, BLOCKTYPE _Green, BLOCKTYPE _Blue)
//     {Red=_Red; Green=_Green; Blue=_Blue;}
//     inline colorBlock(const colorBlock& b)
//     {Red=b.Red; Green=b.Green; Blue=b.Blue;}
//     inline BLOCKTYPE operator[](int Index)
//     {return Array[Index];}
//     inline static const _TCHAR* const ToString(colorEnum color)
//     {
//         switch(color) {
//             case colorRed: return _T("Red");
//             case colorGreen: return _T("Green");
//             case colorBlue: return _T("Blue");
//             default: return 0;
//         }
//     }
// };

// which can be used as follows:
// colorBlock Pixel;
// Pixel.Green = 124; // activates green;
// std::cout << _T("Green=") << Pixel.Green << std::endl;
// std::cout << _T("Red=") << Pixel.Array[colorBlock::colorGreen] << std::endl;
// std::cout << _T("Blue=") << Pixel[2] << std::endl;

#ifndef BLOCKTYPES
#error BLOCKTYPES MUST BE DEFINED FOR THIS FILE TO WORK
#endif
#ifndef BLOCKNAME
#error BLOCKNAME MUST BE DEFINED FOR THIS FILE TO WORK
#endif
#ifndef BLOCKTYPE
#define BLOCKTYPE int
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

struct glue(BLOCKNAME,Block) {
#define SEPERATOR(x) glue(BLOCKNAME,x),
    enum glue(BLOCKNAME,Enum) {BLOCKTYPES};
    union {
#undef SEPERATOR
#define SEPERATOR(x) 1+
        BLOCKTYPE  Array[BLOCKTYPES 0];
        struct {
#undef SEPERATOR
#define SEPERATOR(x) BLOCKTYPE x; 
            BLOCKTYPES
        };
    };
    inline glue(BLOCKNAME,Block)()
    {}
#undef SEPERATOR
#define SEPERATOR(x) BLOCKTYPE glue(_,x),
    inline glue(BLOCKNAME,Block)(BLOCKTYPES BLOCKTYPE Extra=0) //extra value because SEPERATOR ends in comma :(  It's totally ignored.
#undef SEPERATOR
#define SEPERATOR(x) x=glue(_,x);
    {BLOCKTYPES}
    inline glue(BLOCKNAME,Block)(const glue(BLOCKNAME,Block)& b)
#undef SEPERATOR
#define SEPERATOR(x) x=glue(b.,x);
    {BLOCKTYPES}
    inline BLOCKTYPE operator[](int Index)
    {return Array[Index];}
    inline static const _TCHAR* const ToString(glue(BLOCKNAME,Enum) BLOCKNAME)
    {
        switch(BLOCKNAME) {
#undef SEPERATOR
#define SEPERATOR(x) case glue(BLOCKNAME,x): return _T(#x);
            BLOCKTYPES;
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
#undef BLOCKTYPES
#undef BLOCKNAME
#undef BLOCKTYPE
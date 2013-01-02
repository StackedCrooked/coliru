// vector::emplace
#include <iostream>
#include <vector>
#include <utility>
#include <cstdarg>

struct PRINTFER {
    enum { PF_CHAR = 0, PF_WCHAR, PF_INT, PF_UINT, PF_STR, PF_WSTR };
    char type;
    union {
        char asChar;
        wchar_t asWChar;
        int asInt;
        unsigned int asUInt;
        const char* asStr;
        const wchar_t* asWStr;
    };
};

void dummy(...)
{
}

PRINTFER structerizer(const char& val)
{
    PRINTFER ret;
    ret.type = PRINTFER::PF_CHAR;
    ret.asChar = val;
    return ret;
}
PRINTFER structerizer(const wchar_t& val)
{
    PRINTFER ret;
    ret.type = PRINTFER::PF_WCHAR;
    ret.asWChar = val;
    return ret;
}
PRINTFER structerizer(const int& val)
{
    PRINTFER ret;
    ret.type = PRINTFER::PF_INT;
    ret.asInt = val;
    return ret;
}
PRINTFER structerizer(const unsigned int& val)
{
    PRINTFER ret;
    ret.type = PRINTFER::PF_UINT;
    ret.asUInt = val;
    return ret;
}
PRINTFER structerizer(const char* val)
{
    PRINTFER ret;
    ret.type = PRINTFER::PF_STR;
    ret.asStr = val;
    return ret;
}
PRINTFER structerizer(const wchar_t* val)
{
    PRINTFER ret;
    ret.type = PRINTFER::PF_WSTR;
    ret.asWStr = val;
    return ret;
}
int size_calculator(size_t nArgCount, ...)
{
    if (!nArgCount)
        return 0;
    
    unsigned int i = 0;
    int sum = 0;
    
    printf("# of Arguments = %lu, Sizes are:\n", nArgCount);
    
    va_list marker; 
    va_start( marker, nArgCount ); /* Initialize variable arguments. */ 
    
    while( i++ < nArgCount )
    { 
        int nSize = va_arg( marker, int);
        printf("	Arg # %u size = %d\n", i, nSize);
        sum += nSize;
    }
    va_end( marker ); /* Reset variable arguments. */
    return sum;
}

template <typename T>
int report_size(const T& val)
{
    //std::cout << "sizeof value:" << sizeof(val) << std::endl;
    //printf("sizeof(T) = %lu\n", sizeof(val));
    return sizeof(val);
}
/* Template specialization */
template <>
int report_size(const int& val)
{
    //std::cout << "sizeof int value:" << sizeof(val) << std::endl;
    //printf("sizeof(int) = %lu\n", sizeof(val));
    return sizeof(val);
}

/* Overloaded printFmt's */
void printFmt(int i, char val)
{
    printf("%d: = %c\n", i, val);
}
void printFmt(int i, int val)
{
    printf("%d: = %d\n", i, val);
}
void printFmt(int i, const char* val)
{
    printf("%d: = %s\n", i, val);
}

template <typename T>
int print_helper( int n, const T& val)
{    
    //std::cout << n << ": =" << val << std::endl;
    printFmt(n, val);
    return n;
}

template <typename T, typename... Args>
void print_helper(int n, const T& val, const Args&... args)
{
    //std::cout << n << ": =" << val << std::endl;
    printFmt(n, val);
    print_helper(++n, args...);
}


void print_structerizers(size_t nArgCount, ...)
{
    unsigned int i = 0;
    
    printf("# of Arguments = %lu, Values are:\n", nArgCount);
    
    va_list marker; 
    va_start( marker, nArgCount ); /* Initialize variable arguments. */ 
    
    while( i++ < nArgCount )
    { 
        //const char *sOut;
        PRINTFER PF = va_arg( marker, PRINTFER );
        printf("\tArg #%u = ", i);
        switch (PF.type)
        {
            case PRINTFER::PF_CHAR:
                printf("%c", PF.asChar);
                break;
            case PRINTFER::PF_WCHAR:
                printf("%lc", PF.asWChar);
                break;
            case PRINTFER::PF_INT:                
                printf("%d", PF.asInt);
                break;
            case PRINTFER::PF_UINT:
                printf("%u", PF.asUInt);
                break;
            case PRINTFER::PF_STR:
                fputs(PF.asStr, stdout);
                break;
            case PRINTFER::PF_WSTR:
                fputws(PF.asWStr, stdout);
                break;
            default:
                printf("?");
        }
        puts("");
    }
    va_end( marker ); /* Reset variable arguments. */
}


template <typename... Args>
void TestVariadic(const Args&... args)
{
    //auto n = size_calculator(sizeof...(args), report_size<Args>(args)...);
    //printf("Total from size_calculator(): %d\n\n", n);
    
    print_structerizers(sizeof...(args), structerizer(args)...);
    
    printf("sizeof...(args): %lu, vs sizeof...(Args): %lu\n\n", sizeof...(args), sizeof...(Args));
    
    //int n = 1 + (0, report_size<Args>(args)..., 4);
    //print_helper(1, report_size<Args>(args)...);
    
    //print_helper(1, args...);
}

int main ()
{
  int p = 5;
  TestVariadic(4, 'a', p, "string");

  return 0;
}
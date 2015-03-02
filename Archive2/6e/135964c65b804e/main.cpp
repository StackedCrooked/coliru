//
//[pedram heydarinia]>pedram.heydarinia@hotmail.com
//
#define Phoenix_Platform_Linux_Desktop
//
//Language support
#include <cstddef> //<stddef.h>
#include <limits>
#include <climits> //<limits.h>
#include <cfloat> //<float.h>
#include <cstdint> //<stdint.h>
#include <cstdlib> //<stdlib.h>
#include <new>
#include <typeinfo> //<typeinfo.h>
#include <exception>
#include <cstdarg> //<stdarg.h>
#include <csetjmp> //<setjmp.h>
#include <ctime> //<time.h>
#include <csignal> //<signal.h>
#include <cstdbool> //<stdbool.h>
//
//Diagnostics
#include <stdexcept>
#include <cassert> //<assert.h>
#include <cerrno> //<errno.h>
#include <system_error>
//
//General utilities
#include <utility>
#include <ratio>
#include <tuple>
#include <bitset>
#include <type_traits>
#include <functional> //unary_function
#include <memory> //<memory.h>
#include <chrono>
#include <typeindex>
//
//Strings
#include <string>
#include <cctype> //<ctype.h>
#include <cwctype> //<wctype.h>
#include <cstring> //<string.h>
#include <cwchar> //<wchar.h>
//#include <cuchar> //<uchar.h>
//
//Localization
#include <locale>
#if defined(Phoenix_IDE_MSVS) //&& defined(Phoenix_Platform_Windows_Desktop)
#include <codecvt>
#endif
#include <clocale> //<locale.h>
//
//Sequence & Associative Containers & Container adapters
#include <array>
#include <forward_list>
#include <list> //'list' Doubly linked list, rapid insertion and deletion anywhere.
#include <deque> //'deque' Rapid insertions and deletions at front or back.Direct access to any element.
#include <queue> //'queue' queue : First in first out(FIFO) | priority_queue : Highest priority element is always the first element out.
#include <stack> //'stack' Last - in, first - out(LIFO).
#include <vector> //'vector' Rapid insertions and deletions at back.Direct access to any element
#include <unordered_map>
#include <map> //'map' One to one mapping, duplicates not allowed, rapid key based lookup | 'multimap' One to many mapping, duplicates allowed, rapid key based lookup
#include <unordered_set>
#include <set> //'set' Rapid lookup, no duplicates allowed | 'multiset' Rapid lookup, duplicates allowed.
//
//Iterators
#include <iterator>
//
//Algorithms
#include <algorithm> //remove_if
//
//Numerics
#include <cfenv> //<fenv.h>
#include <complex>
#include <random>
#include <valarray>
#include <numeric>
#include <cmath> //<math.h>
#include <ctgmath> //<tgmath.h>
//
//IO support
#include <ios>
#include <iostream>
#include <iosfwd>
#include <istream>
#include <ostream>
#include <streambuf>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdio> //<stdio.h>
#include <cinttypes> //<inttypes.h>
//
//Regular expressions
#include <regex>
//
//Atomic operations
#include <atomic>
//
//Thread support
#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>
//
//Other
#include <ciso646> //<iso646.h>
#include <initializer_list>
//
//RTL
#include <malloc.h>
#include <fcntl.h>
//
//Linux
#include <syslog.h>
#include <dirent.h>
#include <getopt.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/io.h>
#include <sys/mman.h> //for munmap declarations
#include <sys/wait.h>
#include <sys/timeb.h>
#include <asm/errno.h>
//#include <asm/io.h>
//#include <asm/irq.h>
//#include <asm/uaccess.h>
//#include <linux/module.h>
//#include <linux/linkage.h>
#include <linux/input.h>
//#include <linux/videodev.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/pci.h>
//#include <linux/time.h>
//#include <linux/proc_fs.h>
#include <linux/sched.h>
//#include <linux/ioport.h>
//#include <linux/blk.h>
#include <linux/hdreg.h>
#include <linux/string.h>
//#include <linux/delay.h>
#include <linux/reboot.h>
//#include <linux/spinlock.h>
#include <linux/fs.h>
#include <linux/input.h>
//#include <openssl/applink.c> 
//#include <openssl/bio.h>
//#include <openssl/rand.h>
//#include <openssl/ssl.h>
//#include <openssl/err.h>
//
//
typedef signed   char                         sint8; //__int8
typedef unsigned char                         uint8; //byte
typedef signed   short int                    sint16; //short,__int16
typedef unsigned short int                    uint16;
typedef signed   int                          sint32; //int,__int32
typedef unsigned int                          uint32;
typedef signed   long long int                sint64; //long,__int64,__int128
typedef unsigned long long int                uint64;
typedef float                                 float32; //single
typedef long double                           float64; //double,decimal
typedef char                                  chara;
typedef wchar_t                               charu; //charw
typedef char*                                 chara_ptr; //CharAPtr
typedef char**                                chara_ptrptr; //CharAPtrPtr
typedef wchar_t*                              charu_ptr; //CharUPtr
typedef wchar_t**                             charu_ptrptr; //CharUPtrPtr
typedef void*                                 base_ptr; //BasePtr
typedef void**                                base_ptrptr; //BasePtrPtr
typedef std::wstring                          ustring;
typedef std::string                           astring;
typedef std::vector<uint8>                    bytes;
//
#if defined(max)
#else
#define max(a,b)                              (((a) > (b)) ? (a) : (b))
#endif
//
#if defined(min)
#else
#define min(a,b)                              (((a) < (b)) ? (a) : (b))
#endif
//
//#define PIOVER2                               1.570796326795
//#define HalfPI_                               PIOVER2
//#define PIs_                                  3.14159
//#define PIf_                                  3.14159265358979323846f
//#define PI_                                   3.14159265358979323846/*PI*/
//#define TWOPI                                 6.28318530718
//#define Degree2Radian_(a)                     (a)*((float64)PI_/(float64)(180.00000000))
//#define Radian2Degree_(a)                     (a)*((float64)(180.00000000)/(float64)PI_)
//#define PIdiv180_                             Degree2Radian_(1)
//#define DE2RA                                 0.01745329252
//#define RA2DE                                 57.2957795129
//#define FLATTENING                            1.0/298.26
//#define EIs_                                  2.71828
//
#undef NULL
#define NULL                                  0
#undef VOID
#define VOID                                  0
//
#define fixed                                 static const /*static readonly*/ /*static const*/ /*const static*/ /*const*/ /*Fixed*/
//
//nullptr
//auto
//new
//delete
//
#define typeof(a)                             (typeid(a).name())
#define addressof(a)                          (&a)
#define valueof(a)                            (*a)
//sizeof
//
#define IsSameType(Type,Var)                  (bool)dynamic_cast<Type*>(&Var)
//
#define ChangeReadonlyValue(Type,Var,Value)   const_cast<Type*>(this)->Var = Value
//
#if defined(Phoenix_Platform_Windows_Desktop) && defined(Phoenix_IDE_MSVS)
#define Property(Type,Name,Set,Get)           __declspec(property(get=Get,put=Set))Type Name
#elif defined(Phoenix_Platform_Linux_Desktop)
#define Property(Type,Name,Set,Get)
#endif
//
#define EXTERN                                extern
#define EXTERNC                               EXTERN "C"
#define EXTERNCPP                             EXTERN "C++"
//
#if defined(Phoenix_Platform_Windows_Desktop) && defined(Phoenix_IDE_MSVS) //export
#define EXPORT                                __declspec(dllexport)  /* exported from DLL */
#define IMPORT                                __declspec(dllimport)  /* imported from DLL */
#define NAKED                                 __declspec(naked)  /* no prolog or epilog code added */
#define NORETURN                              __declspec(noreturn)
#define thread_local                          __declspec(thread)
#elif defined(Phoenix_Platform_Linux_Desktop)
#define EXPORT                                __attribute__((visibility("default"))) /*"hidden"*/
#define IMPORT                                __attribute__((visibility("default"))) /*"hidden"*/
#define NAKED
#define NORETURN
// thread_local
#endif
//
#define asmf                                 EXTERNC NAKED
//
#if defined(Phoenix_Platform_Windows_Desktop) && defined(Phoenix_IDE_MSVS) //export
#define asmb()                               __asm
#elif defined(Phoenix_Platform_Linux_Desktop)
#define asmb()                               __asm__
#endif
//
#define pack(a)                              namespace a
#define use(a)                               using namespace a;
//
#define External                               /**/
#define Internal                               /*internal*/
#define Static                                 /**/
#define _0T0_                                  /* <T> */
#define _T_                                    /* T */
#define Generic                              template<typename T>
//
#define Hidden(a)                            Internal a
#define Visible(a)                           EXTERNCPP a EXPORT /*eclass,etype*/
//
#define gtype(a)                             Generic class a
#define gmemb                                Generic
#define stype(a)                             /*static*/ class s
#define smemb                                static
#define itype(a)                             /*interface*/ class a
#define atype(a)                             /*abstract*/ class a
#define amemb                                /*abstract*/
#define vmemb                                virtual
#define omemb                                /*override*/
#define ftype(a)                             /*sealed*/ class a
#define rtype(a)                             class a
#define vtype(a)                             /*union*/ struct a
#define etype(a)                             /*enum*/ enum class a
//
#define dfrom                                :public /*extends,inherits*/ 
#define anddf                                ,public /*And,and_inherits*/
//
//#define be                                   =
//#define inc                                  ++
//#define dec                                  --
//#define ise                                  ==
//#define isne                                 !=
//#define isg                                  >
//#define isge                                 >=
//#define isl                                  <
//#define isle                                 <=
//
#define __if                                 if
#define elif                                 else if
#define els()                               else
//
#define _switch(a)                           switch(a) /*check*/
#define _cas(a)                              case a:
#define _def()                               default:
#define _br                                  break
//
#define __for                                for
//#define when                                 ;
//#define then                                 ;
#define _fore                                for each
#define __do()                               do
#define _whl                                 while

int main(){
}

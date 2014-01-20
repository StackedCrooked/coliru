#define __stdcall
#include <cstdio>
#include <functional>

extern "C" void* IdentifyModuleFromAddr(void* p)
{
    return (void*)1;
}

extern "C" void SaveFrame(void* p)
{
}

extern "C" void* GetFrame()
{
    return 0;
}

enum eArgsType
{
    ARGTYPE_DUMMY,
    ARGTYPE_PATH_IN,
    ARGTYPE_PATH_OUT,
};

template<const char* Symbol, const char* LibName, int nArgs, typename Prototype>
struct path_translator_stdcall;

template<const char* Symbol, const char* LibName, int nArgs, typename Ret, typename... Args>
struct path_translator_stdcall<Symbol, LibName, nArgs, Ret(Args...)>
{
    //static const char* symbol = Symbol;
    //static const char* libname = LibName;
    
    static_assert(nArgs == sizeof...(Args), "Wrong sizeof args");
    
    static const int num_args = nArgs;
    static char argtype[1 + nArgs];       // Ret + Args
    typedef Ret(__stdcall *func_type)(Args...);
    
    static func_type fun;
    
    template<typename... ArgsType>  // All should be char
    path_translator_stdcall(ArgsType... t)
    {
        static_assert(nArgs == sizeof...(ArgsType), "Wrong sizeof args");
    }
    
    static Ret __stdcall call(Args... a)
    {
        
    }
    
    static void asm_call()
    {
        __asm__("                           \n\
            .intel_syntax noprefix          \n\
            .globl _IdentifyModuleFromAddr  \n\
            .globl _SaveFrame               \n\
            .globl _GetFrame                \n\
                                            \n\
            cmp ebp, esp                    \n\
            jnz _HasNoFrame                 \n\
                                            \n\
            _HasFrame:                      \n\
            call _SaveFrame                 \n\
            pop ebp                         \n\
            jmp _CallFindMod                \n\
                                            \n\
            _HasNoFrame:                    \n\
            push ebp                        \n\
            call _SaveFrame                 \n\
            add esp, 4                      \n\
                                            \n\
            _CallFindMod:                   \n\
            push [esp]                      \n\
            call _IdentifyModuleFromAddr    \n\
            add  esp, 4                     \n\
                                            \n\
            call %P0                        \n\
                                            \n\
            push eax                        \n\
            call _GetFrame                  \n\
            mov ebp, eax                    \n\
            pop eax                         \n\
                                            \n\
            .att_syntax prefix              \n\
        " : : "i"(call));
    }
    
    
    static void add(uintptr_t addr)
    {
        //fun = ReadMemory<func_type>(addr, false);     // <<|
        //WriteMemory<func_type>(addr, (func_type) asm_call, false);    // false or true?
        
    }
    
    
};





extern const char symbol[] = "_Symbol@4";
extern const char libname[] = "libname.dll";

int main()
{
    path_translator_stdcall<symbol, libname, 1, void(const char*)> a(ARGTYPE_PATH_IN);
    a.add(0);
}

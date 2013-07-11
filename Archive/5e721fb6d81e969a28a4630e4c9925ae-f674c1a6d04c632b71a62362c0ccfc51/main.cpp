//C++ CODE:
template<unsigned caseval> 
unsigned strHash(char const* in, unsigned hash=0) {
    return
      caseval==0 ? *in ? strHash<1>(in,hash) : strHash<4>(in,hash)
    : caseval==1 ? strHash<2>(in,hash+*in)
    : caseval==2 ? strHash<3>(in,hash+(hash<<10))
    : caseval==3 ? strHash<0>(in+1,hash^(hash>>6))
    : caseval==4 ? strHash<5>(in,hash+(hash<<3))
    : caseval==5 ? strHash<6>(in,hash^(hash>>11))
    : caseval==6 ? hash+(hash<<15)
    : hash; //error condition: abort
}

int main(int argc, const char** argv) {
    return strHash<0>(argv[0]);
}

//ASSEMBLY PRODUCED BY MSVC11 RELEASE BUILD
int main(int argc, const char** argv) {
011F1002  in          al,dx  
    return strHash<0>(argv[0]);
011F1003  mov         eax,dword ptr [argv]  
011F1006  mov         ecx,dword ptr [eax]  
011F1008  mov         al,byte ptr [ecx]  
011F100A  test        al,al  
011F100C  je          main+25h (011F1025h)  
011F100E  movsx       eax,al  
011F1011  imul        eax,eax,401h  
011F1017  mov         edx,eax  
011F1019  shr         edx,6  
011F101C  xor         edx,eax  
011F101E  inc         ecx  
}
011F101F  pop         ebp  
    return strHash<0>(argv[0]);
011F1020  jmp         strHash<0> (011F1030h)  
011F1025  xor         edx,edx  
}
011F1027  pop         ebp  
    return strHash<0>(argv[0]);
011F1028  jmp         strHash<4> (011F1060h)  

--- c:\users\tbohne\dropbox\code\test\test\main.cpp ----------------------------
    return
      caseval==0 ? *in ? strHash<1>(in,hash) : strHash<4>(in,hash)
    : caseval==1 ? strHash<2>(in,hash+*in)
    : caseval==2 ? strHash<3>(in,hash+(hash<<10))
    : caseval==3 ? strHash<0>(in+1,hash^(hash>>6))
    : caseval==4 ? strHash<5>(in,hash+(hash<<3))
    : caseval==5 ? strHash<6>(in,hash^(hash>>11))
    : caseval==6 ? hash+(hash<<15)
    : hash; //error condition: abort
011F1030  mov         al,byte ptr [ecx]  
011F1032  test        al,al  
011F1034  je          strHash<0>+1Eh (011F104Eh)  
011F1036  movsx       eax,al  
011F1039  add         eax,edx  
011F103B  imul        eax,eax,401h  
011F1041  mov         edx,eax  
011F1043  shr         edx,6  
011F1046  xor         edx,eax  
011F1048  inc         ecx  
011F1049  jmp         strHash<0> (011F1030h)  
011F104E  jmp         strHash<4> (011F1060h)  

--- c:\users\tbohne\dropbox\code\test\test\main.cpp ----------------------------
strHash<4>:
011F1060  lea         ecx,[edx+edx*8]  
011F1063  mov         eax,ecx  
011F1065  shr         eax,0Bh  
011F1068  xor         eax,ecx  
011F106A  imul        eax,eax,8001h  
}
011F1070  ret  

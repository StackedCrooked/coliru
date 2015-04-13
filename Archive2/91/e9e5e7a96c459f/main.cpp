__declspec(noinline) void testSTD() {
00251CF0  push        ecx  
00251CF1  xorps       xmm1,xmm1  
    //std::cout << "STD\t";
    //auto start=std::chrono::high_resolution_clock::now();
    double res = 0.0;
00251CF4  mov         edx,3E8h  
00251CF9  lea         esp,[esp]  
        res = std::inner_product(a1.begin(), a1.end(), a2.begin(), res);
00251D00  xor         ecx,ecx  
00251D02  jmp         testSTD+20h (0251D10h)  
00251D04  lea         esp,[esp]  
00251D0B  jmp         testSTD+20h (0251D10h)  
00251D0D  lea         ecx,[ecx]  
00251D10  movsd       xmm0,mmword ptr [ecx+277C70h]  
00251D18  mulsd       xmm0,mmword ptr [ecx+4EC3070h]  
00251D20  add         ecx,8  
00251D23  lea         eax,[ecx+277C70h]  
00251D29  addsd       xmm1,xmm0  
00251D2D  cmp         eax,4EC3070h  
00251D32  jne         testSTD+20h (0251D10h)  
    for (size_t z = 0; z < REPS; z++) {
00251D34  dec         edx  
00251D35  jne         testSTD+10h (0251D00h)  
    }
    //auto end = std::chrono::high_resolution_clock::now();
    //auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << res ;//<< '\t' << dur.count() << '\n';
00251D37  call        std::basic_ostream<char,std::char_traits<char> >::operator<< (0252070h)  
00251D3C  pop         ecx  
}
00251D3D  ret  




__declspec(noinline) void testManual() {
00251D40  push        ecx  
00251D41  xorps       xmm2,xmm2  
    //std::cout << "Manual\t";
    //auto start=std::chrono::high_resolution_clock::now();
    double res = 0.0;
00251D44  mov         ecx,3E8h  
00251D49  lea         esp,[esp]  
        for (size_t t = 0; t < N; ++t)  {
00251D50  xor         eax,eax  
00251D52  jmp         testManual+20h (0251D60h)  
00251D54  lea         esp,[esp]  
00251D5B  jmp         testManual+20h (0251D60h)  
00251D5D  lea         ecx,[ecx]  
            res += a1[t] * a2[t];
00251D60  movupd      xmm1,xmmword ptr [eax+4EC3070h]  
00251D68  movupd      xmm0,xmmword ptr [eax+277C70h]  
00251D70  add         eax,10h  
00251D73  mulpd       xmm1,xmm0  
            res += a1[t] * a2[t];
00251D77  addpd       xmm2,xmm1  
00251D7B  cmp         eax,4C4B400h  
00251D80  jb          testManual+20h (0251D60h)  
    for (size_t z = 0; z < REPS; z++) {
00251D82  dec         ecx  
00251D83  jne         testManual+10h (0251D50h)  
        }
    }
    //auto end = std::chrono::high_resolution_clock::now();
    //auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << res;// << '\t' << dur.count() << '\n';
00251D85  movaps      xmm1,xmm2  
00251D88  unpckhpd    xmm1,xmm2  
00251D8C  addsd       xmm1,xmm2  
00251D90  call        std::basic_ostream<char,std::char_traits<char> >::operator<< (0252070h)  
00251D95  pop         ecx  
}
00251D96  ret  
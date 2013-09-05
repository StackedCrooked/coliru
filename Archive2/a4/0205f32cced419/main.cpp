    #include <iostream>
    
    
    bool test1(bool a, bool b, bool c)
    {
        return a | b | c;
    }
    
    bool test2(bool a, bool b, bool c)
    {
        return a || b || c;
    }
    
    int main()
    {
      bool a = true;
      bool b = false;
      bool c = true;
      test1(a,b,c);
      test2(a,b,c);
      return 0;
    }

    
    _Z5test2bbb:
    .LFB1265:
        .cfi_startproc
    	test	dil, dil
    	jne	.L6
    	test	sil, sil
    	mov	eax, edx
    	jne	.L6
    	rep; ret
    	.p2align 4,,10
    	.p2align 3
    .L6:
    	mov	eax, 1
    	ret
    	.cfi_endproc
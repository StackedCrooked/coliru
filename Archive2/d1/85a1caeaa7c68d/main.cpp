fn:
    pushl   %ebp
    movl    $1, %eax
    movl    %esp, %ebp
    movl    8(%ebp), %edx 
    cmpl    $1, %edx\\ compare variable1 to 1
    jle .L4\\ less than or equal jump.
.L5:
    imull   %edx, %eax\\ multiply variable1 by variable 2
    subl    $1, %edx\\ variable1 -1
    cmpl    $1, %edx\\ compare variable1 with 1
    jne .L5 Loop if not equal
.L4:
    popl    %ebp\\ return value
    ret
    
    
//direct:
int func(int x)
{                               // pushl   %ebp
    //...=1;                    // movl    $1, %eax
    int local=1;                // movl    %esp, %ebp
    //...x...                   // movl    8(%ebp), %edx 
    //...0<x...                 // cmpl    $1, %edx
    if (x>=0)                   // jle .L4
    { 
        do {                    // .L5:
            local*=x;           // imull   %edx, %eax
            local-=1;           // $1, %edx\\ variable1 -1
            //...local==1...    // cmpl    $1, %edx
        } while(local==1);      // jne .L5
    }                           // .L4:
    return local;               // popl    %ebp
}                               // ret

//normalized:
int func(int x)
{
    int local;
    for(local=1; local<x; --local)
        local *= x;
    return local;
}
#if !defined(INITIALIZE)
#   define INITIALIZE
#   define THIS __FILE__
#   define B6 0
#   define B5 0
#   define B4 0
#   define B3 0
#   define B2 0
#   define B1 0
#   define B0 0
#   define R2 0
#   define R1 0
#   define R0 0
#   define BS (B6,B5,B4,B3,B2,B1,B0)
#   define EVAL(Y) Y
#   define PI(X,Y) X##Y
#   define P(X,Y) PI(X,Y)
#   define DONEXT(A) DONEXTI(P(TERM,A),1,~)
#   define DONEXTI(A,B,...) DONEXTII(A,B,__VA_ARGS__)
#   define DONEXTII(A,B,...) B
#   define LDM0 ,
#   define LDM00 ,
#   define GLUENOZ(A,B,C) GLUENOZI(P(LDM,P(A,B)) P(LDM,A),C,B,A,~)
#   define GLUENOZI(X,C,B,A,...) GLUENOZII(X,C,B,A,__VA_ARGS__)
#   define GLUENOZII(X,C,B,A,...) P(A,P(B,C))
#   define TERM100 ,0,
#   define BX(A,B,C,D,E,F,G) (A<<6)|(B<<5)|(C<<4)|(D<<3)|(E<<2)|(F<<1)|(G)
#   define X (EVAL(BX BS))+1
#   define R EVAL(GLUENOZ(R2,R1,R0))
#   define GETRES
#   include THIS
#   define MAINLOOP
#   include THIS
#elif defined(MAINLOOP)
#   undef MAINLOOP
#   if (!(R%3)&&!(R%5))
FizzBuzz
#   elif (!(R%3))
Fizz
#   elif (!(R%5))
Buzz
#   else
R
#   endif
#   if DONEXT(R)
#      define GETBIN
#      include THIS
#      define GETRES
#      include THIS
#      define MAINLOOP
#      include THIS
#   endif
#elif defined(GETBIN)
#   undef GETBIN
#   undef B0
#   undef B1
#   undef B2
#   undef B3
#   undef B4
#   undef B5
#   undef B6
#   undef B7
#   if ((R2*100+R1*10+R0)&1)
#      define B0 1
#   else
#      define B0 0
#   endif
#   if ((R2*100+R1*10+R0)&2)
#      define B1 1
#   else
#      define B1 0
#   endif
#   if ((R2*100+R1*10+R0)&4)
#      define B2 1
#   else
#      define B2 0
#   endif
#   if ((R2*100+R1*10+R0)&8)
#      define B3 1
#   else
#      define B3 0
#   endif
#   if ((R2*100+R1*10+R0)&16)
#      define B4 1
#   else
#      define B4 0
#   endif
#   if ((R2*100+R1*10+R0)&32)
#      define B5 1
#   else
#      define B5 0
#   endif
#   if ((R2*100+R1*10+R0)&64)
#      define B6 1
#   else
#      define B6 0
#   endif
#   if ((R2*100+R1*10+R0)&128)
#      define B7 1
#   else
#      define B7 0
#   endif
#elif defined(GETRES)
#   undef GETRES
#   undef R2
#   undef R1
#   undef R0
#   if   (((X)%10)==1)
#      define R0 1
#   elif (((X)%10)==2)
#      define R0 2
#   elif (((X)%10)==3)
#      define R0 3
#   elif (((X)%10)==4)
#      define R0 4
#   elif (((X)%10)==5)
#      define R0 5
#   elif (((X)%10)==6)
#      define R0 6
#   elif (((X)%10)==7)
#      define R0 7
#   elif (((X)%10)==8)
#      define R0 8
#   elif (((X)%10)==9)
#      define R0 9
#   else
#      define R0 0
#   endif
#   if   ((((X)/10)%10)==1)
#      define R1 1
#   elif ((((X)/10)%10)==2)
#      define R1 2
#   elif ((((X)/10)%10)==3)
#      define R1 3
#   elif ((((X)/10)%10)==4)
#      define R1 4
#   elif ((((X)/10)%10)==5)
#      define R1 5
#   elif ((((X)/10)%10)==6)
#      define R1 6
#   elif ((((X)/10)%10)==7)
#      define R1 7
#   elif ((((X)/10)%10)==8)
#      define R1 8
#   elif ((((X)/10)%10)==9)
#      define R1 9
#   else
#      define R1 0
#   endif
#   if   ((((X)/100)%10)==1)
#      define R2 1
#   else
#      define R2 0
#   endif
#endif

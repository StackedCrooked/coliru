#include <stdlib.h>
#define d(b,c) (((unsigned)(b))&((unsigned)(c))?1:0) /* detector */
#define c(a,b,c) ((((unsigned)(a))<<c)|((unsigned)(b))) /* combinator */
#define b(w,x,y,z) c[c(c(c(w,x,8),y,8),z,8)] /* charmap hypercube */
#define p(w,x,y,z) sprintf(f,"%d.%d.%d.%d.ppm",w,x,y,z);freopen(f,"w",stdout);p6
;
#define p6 printf("P6 256 256 1\n"); /* http://netpbm.sf.net/doc/ppm.html */
#define rgb(c) printf("%c%c%c",d(c,4),d(c,2),d(c,1))
/*: weltformel; gdb $<
%: %.c; cc -o $@ -g $<
%: exit */
        main(){char w,x,y,z,*c=calloc(1L<<32,sizeof(char));
        for(w=0;--w;)for(z=0;z--;)for(y=0;y--;)for(x=0;x--;)b(w,x,y,z)=(x+y+z)%2?1:4;
        b(10,0,0,0)=7; /* urknall! 10 is just random choice */
        for(w=1;w>0;)for(z=0;z--;)for(y=0;y--;)for(x=0;x--;){
                char q=b(w-1,x,y,z); /* current chromodynamic */
                char d=d(8,q)?-1:+1; /* director == utm23state */
                char a=d(1,b(w-1,x,y,z))? b(w-1,x+d,y,z) : /* directed tape scan */
                       d(2,b(w-1,x,y,z))? b(w-1,x,y+d,z) : b(w-1,x,y,z+d);
                b(w,x,y,z)=c(d(d,+1),c(d(q^a,4),c(d(q^a,2),d(q^a,1),1),1),1);
        } /* now i have computed the first 127 planck units of the evolution */
        for(w=1;w>0;)for(z=0;z--;)for(y=0;y--;)for(x=0;x--;){
                static char f[]="-127.-127.-127.-127.ppm"; int X, Y;
                p(w,256,256,z);for(X=-128;X<128;++X)for(Y=-128;Y<128;++Y)rgb(b(w,X,Y,z));
                p(w,256,y,256);for(X=-128;X<128;++X)for(Y=-128;Y<128;++Y)rgb(b(w,X,y,Y));
                p(w,x,256,256);for(X=-128;X<128;++X)for(Y=-128;Y<128;++Y)rgb(b(w,x,X,Y));
                p(256,x,y,256);for(X=-128;X<128;++X)for(Y=-128;Y<128;++Y)rgb(b(X,x,y,Y));
                p(256,x,256,z);for(X=-128;X<128;++X)for(Y=-128;Y<128;++Y)rgb(b(X,x,Y,z));
                p(256,256,y,z);for(X=-128;X<128;++X)for(Y=-128;Y<128;++Y)rgb(b(X,Y,y,z));
        }} /* complete axis-parallel imaging of the computed universe saved */
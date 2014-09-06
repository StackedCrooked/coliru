void egcd(int a, int b, int buf[4]) {
    int q, r;
    int s = 0, t = 1;
    int u = 1, v = 0;
    
    do {
        q = a / b;
        r = a % b;
        a = b;
        b = r;
        
        s = u - q*s;
        t = v - q*t;
        u = s;
        v = t;

        //printf("q:%d,b:%d, u:%d, s:%d v:%d t:%d while!\n",q,b,u,s,v,t);
    } while(b!=0);

     // a = gcd ; u = modular multiplicative inverse ; v and s : internal use only
     buf[0] = a;
     buf[1] = u;
     buf[2] = v;
     buf[3] = s;
}
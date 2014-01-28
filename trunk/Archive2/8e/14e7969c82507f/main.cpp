    #include <stdio.h>

    int x,y;

    void p(int n){
        x=(n+2)/(n+3);
    }

    void q(){
        int x,y;
        x=3;
        y=4;
        p(y);
        printf("%d", x);
    }

    int main(){
        x=7;
        y=8;
        q();
        printf("%d", x);
    }
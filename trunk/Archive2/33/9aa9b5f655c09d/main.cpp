# include <fstream>
using namespace std;
ifstream f("cladiri2.in");
ofstream g("cladiri2.out");
int n,nr,i,og,pal,j,nr1,nr2,nc,x,v[10000],b[1000],nc1,nr3,cladiri,y,c,a,d,cuburi,max1,uc;
int main(){
    f>>n;
    for(i=1;i<=n;i++){
        f>>nr;
        nr1=nr2=nr3=nr;
        while(nr>9){
            nc=0;
            v[nc+1]=nr%10;
            nr=nr/10;
            nc=nc+1;
        }
        x=x+nc;
        b[i]=nc;
        for(j=2;j<=nc;j++){
            max1=v[1];
            if(max1<v[j])
                max1=v[j];
        }
        while(c==0){
            y=nr1%10;
            nr1=nr1/10;
            if(y==max1)
                cladiri++;
        }
        while(nr2!=0){
            x=1;
            uc=nr2%10;
            og=og+uc*x;
            x=x*10;
            nr2=nr2/10;
            if(nr2==nr3)
                pal++;
            else{
                a=nr3/10;
                d=nr3%10;
                if(a==d)
                    nr3=(nr3%x)/10;
                else{
                    nr3=(nr3%x)/10;
                    if(a>d)
                        cuburi=cuburi+(a-d);
                    if(d>a)
                        cuburi=cuburi+(d-a);
                x=x/10;
                a=0;
                d=0;
       }
    }
        }
    g<<max1<<' ';
    g<<cladiri<<'\n';
    g<<pal<<'\n';
    g<<cuburi<<'\n';
    g.close();
    return 0;
}
}

int collatztwo(int a){
int temp, num;
//num = a;

temp = 0;

while(a != 1){
    if(a%2 == 0){
    a = a/2;
    temp++;
    }
    else if(a&2 != 0){
        a = (3*a) + 1;
        temp++;
    }

}
//cout <<  "looped: " << temp;
return 0;}

int main (){
    
	int f[10] = {0, -1, -2, -3, -4, -5, -6, -7, -8, -9};
	int values[2] = {7,3};
	int *pos;
	int x = 0;
	while (x <10){
		pos = f + x; // pos ist die adresse von dem array f[x], also &f[x], wie davor
		x+=2;
		*pos = (int)(&x); //*pos = f[x], f[x] = &x, also nur jede zweite stelle vom array f ändert sich zur adresse von x, die bei 2000 ist
			} // es wird von 0 hochgezählt bist 10; wegen x+=2  und x<10 wird dann nur jeweils 0,2,4,6,8 abgelaufen
}

//adresse von f: wie davor, 1000 - 1040 belegt, f[0]-1000, f[1]-1004, f[2]-1008, f[3]-1012, f[4]-1016, f[5]-1020, f[6]-1024,f[7]-1028, f[8]-1032, f[9]-1036
//inhalt von f: f[0]=2000, f[1]=-1, f[2]=2000, f[3]=-3, f[4]=2000, f[5]=-5, f[6]=2000, f[7]=-7, f[8]=2000, f[9]=-9
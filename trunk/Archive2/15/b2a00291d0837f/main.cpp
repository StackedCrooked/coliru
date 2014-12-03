int main(){
    
	int f[10];
	int values[2] = {0,1};
	int *pos;
	int x = 9;

while (x >= 0){
	pos = f + x;        // pos ist die adresse des arrays f an der stelle x also einfach &f[x]
	*pos = *(values+x%2); //*pos ist der Inhalt von pos; *pos ist einfach f[x] wegen pos = f + x
						// *(values+x%2)= *(&values[0]+x%2)= *(&values[x%2]) = values [x%2]; array f hat dann den inhalt von values[x%2]
--x;
}
// Inhalt: f[0]=0, f[1]=1, f[2]=0, f[3]=1, f[4]=0, f[5]=1, f[6]=0, f[7]=1, f[8]=0, f[9]=1

// Adresse: feld belegt insgesamt 40 byte
//f[0]-1000, f[1]-1004, f[2]-1008, f[3]-1012, f[4]-1016, f[5]-1020, f[6]-1024,f[7]-1028, f[8]-1032, f[9]-1036
}
int main(){
    
	int f[10];
	int values[2] = {0,1};
	int *pos;
	int x = 9;

while (x >= 0){
	pos = f + x;
	*pos = *(values+x%2);
--x;
}
}
int refReturn(int &ref){ //return type int
   ref++;
   return ref;
}

int main(){
   int num1 = 1;
   int &num2 = refReturn(num1); //Compile Error
}
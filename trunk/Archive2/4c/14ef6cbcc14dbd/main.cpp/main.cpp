int foo (int x, int y) {
   if (y == 0) return 0;
   return foo(x, --y) % 2;
}

int main () {
   int z = 0;
   for (int i = 0; i < 6; i++) {       
       z = z + foo (1, i);
   }
}

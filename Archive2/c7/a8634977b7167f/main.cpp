namespace N { 
  struct O {}; 
  void func (O) { } 
}

void func (N::O) { } 

int
main (int argc, char *argv[]) {
  (func) (N::O {});
   func  (N::O {});
}
struct X{
  struct Y{} m;
  X operator*(){ return X(); }
};

int main(){
  X* x;
  X::Y&& yr = x->m;
}
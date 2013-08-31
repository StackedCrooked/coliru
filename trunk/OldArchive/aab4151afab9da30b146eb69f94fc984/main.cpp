struct X{
  struct Y{} m;
  X operator*(){ return X(); }
};

int main(){
  X x;
  auto& yr = (*x).m;
}
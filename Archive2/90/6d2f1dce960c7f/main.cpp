int main() {
  int i = 3;
  //if(i == 7) // did you spotted that someone has skipped "="?
  //if(7 == i) // solution 1) Yoda sentance: "if blue is the sky"
  if(i = 7) // <- no Yoda sentance, checked by compiler
  {
    return 4;
  }
  return 0;
}

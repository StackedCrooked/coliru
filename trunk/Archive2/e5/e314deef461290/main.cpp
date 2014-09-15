int main() {return 0;}
struct element;

#ifdef Test2
void dostuff (struct element sv[]) { }
#else
void dostuff (struct element* sv) { }
#endif

struct _ { void operator=(_){}  }; _&operator<(_&__,_&){return __;} _&operator>(_&,_&__){return __;}
_ &Ptr=*(static_cast<_*>(nullptr)), &Node=Ptr, &node=Ptr, *i;

int main() {
    Ptr < Node > node = *i;
}

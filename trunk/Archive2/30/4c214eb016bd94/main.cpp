

Tcl_Obj* toTcl(int n) const
{
    return Tcl_NewIntObj(n);
}


Tcl_Obj* toTcl(bool b) const
{
    return Tcl_NewBooleanObj(b);
}


Tcl_Obj* toTcl(double d) const
{
    return Tcl_NewDoubleObj(d);
}


Tcl_Obj* toTcl(long l) const
{
    return Tcl_NewLongObj(l);
}


Tcl_Obj* toTcl(const std::string& s) const
{
    return Tcl_NewStringObj(const_cast<std::string&>(s).data(), s.size());
}


template<int N>
Tcl_Obj* toTcl(const char (&c)[N]) const
{
    return Tcl_NewStringObj(&c[0], N - 1);
}
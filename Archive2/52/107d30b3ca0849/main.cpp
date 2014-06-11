
template<typename T>
inline Tcl_Obj* toTcl(T&& t)
{ return toTclImpl(std::forward<T>(t), std::common_type<T>); }

inline Tcl_Obj* toTclImpl(int n, std::common_type<int>)
{ return Tcl_NewIntObj(n); }

inline Tcl_Obj* toTclImpl(bool b, std::common_type<bool>)
{ return Tcl_NewBooleanObj(b); }

inline Tcl_Obj* toTclImpl(double d, std::common_type<double>)
{ return Tcl_NewDoubleObj(d); }

inline Tcl_Obj* toTclImpl(long l, std::common_type<long>)
{ return Tcl_NewLongObj(l); }

inline Tcl_Obj* toTclImpl(const std::string& s, std::common_type<std::string>)
{ return Tcl_NewStringObj(const_cast<std::string&>(s).data(), s.size()); }

inline Tcl_Obj* toTclImpl(const char* c, std::common_type<const char*>)
{ return Tcl_NewStringObj(const_cast<char*>(c), strlen(c)); }

template<int N> inline Tcl_Obj* toTclImpl(const char (&c)[N], std::common_type<const char (&)[N]>)
{ return Tcl_NewStringObj(&c[0], N - 1); }

// Unimplemented:
// - tcl unicode character
// - tcl wide int


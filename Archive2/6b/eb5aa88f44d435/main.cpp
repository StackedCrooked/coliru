template<class T>
T* MyClass::New(size_t count) 
{T* r = Reserve<T>(count); return new(r)T();}
template<class T, class Param0>
T* MyClass::New(size_t count, const Param0& p0) 
{T* r = Reserve<T>(count); return new(r)T(p0);}
template<class T, class Param0, class Param1>
T* MyClass::New(size_t count, const Param0& p0, const Param1& p1) 
{T* r = Reserve<T>(count); return new(r)T(p0, p1);}
template<class T, class Param0, class Param1, class Param2>
T* MyClass::New(size_t count, const Param0& p0, const Param1& p1, const Param1& p2) 
{T* r = Reserve<T>(count); return new(r)T(p0, p1, p2);}
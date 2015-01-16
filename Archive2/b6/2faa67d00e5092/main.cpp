            using C = const char*;

            // Final class calls one of these three constructor overloads
            MethodMapItem( C name, F0 func, PyCFunction handler, C doc ) : PyMethodDef{ name, handler, METH_NOARGS               , doc }, f0{func} { };
            MethodMapItem( C name, F1 func, PyCFunction handler, C doc ) : PyMethodDef{ name, handler, METH_VARARGS              , doc }, f1{func} { };
            MethodMapItem( C name, F2 func, PyCFunction handler, C doc ) : PyMethodDef{ name, handler, METH_VARARGS|METH_KEYWORDS, doc }, f2{func} { };

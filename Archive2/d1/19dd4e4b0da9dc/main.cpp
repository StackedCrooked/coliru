        struct Strings {
            std::string m_name, m_doc;
            Strings(std::string n, std::string d) : m_name{n},m_doc{d} {}
        };

        struct MethodMapItem : Strings, PyMethodDef
        {
            // whichever signature matches, that entry gets used
            F0 f0{nullptr};
            F1 f1{nullptr};
            F2 f2{nullptr};

            //const std::string s;
            using S = const std::string;

            S s;

            using C = const char*;

            // Final class calls one of these three constructor overloads
            MethodMapItem( C name, F0 func, PyCFunction handler, C doc ) : Strings{name,doc}, PyMethodDef{ m_name.c_str(), handler, METH_NOARGS               , m_doc.c_str() }, f0{func} { };
            MethodMapItem( C name, F1 func, PyCFunction handler, C doc ) : Strings{name,doc}, PyMethodDef{ m_name.c_str(), handler, METH_VARARGS              , m_doc.c_str() }, f1{func} { };
            MethodMapItem( C name, F2 func, PyCFunction handler, C doc ) : Strings{name,doc}, PyMethodDef{ m_name.c_str(), handler, METH_VARARGS|METH_KEYWORDS, m_doc.c_str() }, f2{func} { };

#define PCF(x) reinterpret_cast<PyCFunction>(x)

    protected:
        // overloads for a new-style class (notice that each method gets its own handler)
        template <F0 f> static void add_method( const char* name, const char* doc="" )  { add_method( name, f, PCF(&handler<f>), doc ); }
        template <F1 f> static void add_method( const char* name, const char* doc="" )  { add_method( name, f, PCF(&handler<f>), doc ); }
        template <F2 f> static void add_method( const char* name, const char* doc="" )  { add_method( name, f, PCF(&handler<f>), doc ); }

    private:

        static FinalClass* final(PyObject* o) { return cxxObject_for<FinalClass>(o); }

        static PyObject* handlerX( int i, std::function<Object()> lambda )
        {
            try
            {
                COUT( i );
                return charge( *lambda() ); // feed charged ref back to Python
            }
            catch( Exception & )
            {
                COUT( "! ! !  Exception Python calling new-style-class handler ! ! !" );
                return 0;
            }
        }

        #define P PyObject*
        template< F0 f > static P handler( P o, P   )      { return handlerX( 0, [&] ()->Object { return (final(o) ->* f)(                         ); }  ); }
        template< F1 f > static P handler( P o, P a )      { return handlerX( 1, [&] ()->Object { return (final(o) ->* f)( to_tuple(a)             ); }  ); }
        template< F2 f > static P handler( P o, P a, P k ) { return handlerX( 2, [&] ()->Object { return (final(o) ->* f)( to_tuple(a), to_dict(k) ); }  ); }
        #undef P

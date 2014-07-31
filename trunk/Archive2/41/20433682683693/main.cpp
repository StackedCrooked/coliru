// Tcl bindings


struct Autocast
{
    Autocast(Tcl_Obj * obj) : obj(obj) { }

    template<typename T>
    operator T() const {
        T result;
        tcl_get(obj, result);
        return result;
    }

    Tcl_Obj * obj;
};


void tcl_get(Tcl_Obj*, bool);
void tcl_get(Tcl_Obj*, double);
void tcl_get(Tcl_Obj*, int);
// etc...


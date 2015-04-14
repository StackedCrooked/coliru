
#include <Python.h>


#include "structmember.h"

static int signal = 41222;

typedef struct {
    int a;
    char b;
    float c;
    double d;
    char* e;
} SimulinkBus ;

SimulinkBus bus = { 42, 'Z', 34.981f, 22./7,"JACK" };

typedef struct {
    PyObject_HEAD
    PyObject *first;
    PyObject *last;
    int number;
    int* ptr;
    SimulinkBus* sptr ;
} Noddy;

static void
Noddy_dealloc(Noddy* self)
{
    Py_XDECREF(self->first);
    Py_XDECREF(self->last);
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
Noddy_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Noddy *self;

    self = (Noddy *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->first = PyString_FromString("");
        if (self->first == NULL)
          {
            Py_DECREF(self);
            return NULL;
          }
        
        self->last = PyString_FromString("");
        if (self->last == NULL)
          {
            Py_DECREF(self);
            return NULL;
          }

        self->number = 0;
        self->ptr = &signal ;
         self->sptr = &bus ;
    }

    return (PyObject *)self;
}

static int
Noddy_init(Noddy *self, PyObject *args, PyObject *kwds)
{
    PyObject *first=NULL, *last=NULL, *tmp;

    static char *kwlist[] = {"first", "last", "number", NULL};

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|SSi", kwlist, 
                                      &first, &last, 
                                      &self->number))
        return -1; 

    if (first) {
        tmp = self->first;
        Py_INCREF(first);
        self->first = first;
        Py_DECREF(tmp);
    }

    if (last) {
        tmp = self->last;
        Py_INCREF(last);
        self->last = last;
        Py_DECREF(tmp);
    }
    self->ptr = &signal ;
    self->sptr = &bus ;
    return 0;
}

static PyMemberDef Noddy_members[] = {
    {"number", T_INT, offsetof(Noddy, number), 0,
     "noddy number"},
    {NULL}  /* Sentinel */
};

static PyObject *
Noddy_getfirst(Noddy *self, void *closure)
{
    Py_INCREF(self->first);
    return self->first;
}

static int
Noddy_setfirst(Noddy *self, PyObject *value, void *closure)
{
  if (value == NULL) {
    PyErr_SetString(PyExc_TypeError, "Cannot delete the first attribute");
    return -1;
  }
  
  if (! PyString_Check(value)) {
    PyErr_SetString(PyExc_TypeError, 
                    "The first attribute value must be a string");
    return -1;
  }
      
  Py_DECREF(self->first);
  Py_INCREF(value);
  self->first = value;    

  return 0;
}

static PyObject *
Noddy_getlast(Noddy *self, void *closure)
{
    Py_INCREF(self->last);
    return self->last;
}

static int
Noddy_setlast(Noddy *self, PyObject *value, void *closure)
{
  if (value == NULL) {
    PyErr_SetString(PyExc_TypeError, "Cannot delete the last attribute");
    return -1;
  }
  
  if (! PyString_Check(value)) {
    PyErr_SetString(PyExc_TypeError, 
                    "The last attribute value must be a string");
    return -1;
  }
      
  Py_DECREF(self->last);
  Py_INCREF(value);
  self->last = value;    

  return 0;
}

static PyObject *
Noddy_getptr(Noddy *self, void *closure)
{
    // char buf[8];
    // memcpy( buf, self->ptr, sizeof(int));
    // return Py_BuildValue("s#", buf,  sizeof(int)) ;
    return Py_BuildValue("s#",  (char* )self->ptr,  sizeof(int)) ;
}

static int
Noddy_setptr(Noddy *self, PyObject *value, void *closure)
{
  if (value == NULL) {
    PyErr_SetString(PyExc_TypeError, "Cannot delete the last attribute");
    return -1;
  }
  
  // if (! PyString_Check(value)) {
    // PyErr_SetString(PyExc_TypeError, 
                    // "The last attribute value must be a string");
    // return -1;
  // }
      
  Py_DECREF(self->last);
  Py_INCREF(value);
  int len;
  char *b;
  if( PyArg_Parse(value, "s#", &b, &len ) ) 
  {
    char ss[32];
    sprintf( ss, "val =%s, len = %d", b, len ) ;
 
    // PyErr_SetString(PyExc_TypeError, ss );
   
    self->ptr = (int *)b;    
  }

  return 0;
}


static PyObject *
Noddy_busptr(Noddy *self, void *closure)
{
    return Py_BuildValue("s#",  (char* )self->sptr,  sizeof(SimulinkBus)) ;
}


static PyGetSetDef Noddy_getseters[] = {
    {"first", (getter)Noddy_getfirst, (setter)Noddy_setfirst, "first name", NULL },
    {"last",  (getter)Noddy_getlast, (setter)Noddy_setlast, "last name", NULL },
    {"ptr",  (getter)Noddy_getptr, (setter)Noddy_setptr, "ptr val", NULL },
    {"sptr",  (getter)Noddy_busptr, NULL, "sptr val", NULL },
    {NULL}  /* Sentinel */
};

static PyObject *
Noddy_name(Noddy* self)
{
    static PyObject *format = NULL;
    PyObject *args, *result;

    if (format == NULL) {
        format = PyString_FromString("%s %s");
        if (format == NULL)
            return NULL;
    }

    args = Py_BuildValue("OO", self->first, self->last);
    if (args == NULL)
        return NULL;

    result = PyString_Format(format, args);
    Py_DECREF(args);
    
    return result;
}

static PyMethodDef Noddy_methods[] = {
    {"name", (PyCFunction)Noddy_name, METH_NOARGS,
     "Return the name, combining the first and last name"
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject NoddyType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "noddy.Noddy",             /*tp_name*/
    sizeof(Noddy),             /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)Noddy_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "Noddy objects",           /* tp_doc */
    0,    	               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    Noddy_methods,             /* tp_methods */
    Noddy_members,             /* tp_members */
    Noddy_getseters,           /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Noddy_init,      /* tp_init */
    0,                         /* tp_alloc */
    Noddy_new,                 /* tp_new */
};

static PyMethodDef module_methods[] = {
    {NULL}  /* Sentinel */
};

const char *keys[] ={
"king", "queen", "jack"
};

int main(int argc, char *argv[])
{
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue, *m, *PySimulinkBus ;
    int i, status;

    if (argc < 3) {
        fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
        return 1;
    }

    Py_Initialize();
    
    if (PyType_Ready(&NoddyType) < 0)
    {
        printf("Not Ready !" );
        return -1;
    }    
    pName = PyString_FromString(argv[1]);
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    
    m = Py_InitModule3("noddy", module_methods,
                        "Example module that creates an extension type.");

    if (m == NULL)
      return -1;
      // assert( 2+2==5 );
    Py_INCREF(&NoddyType);
    status = PyModule_AddObject(m, "Noddy", (PyObject *)&NoddyType);
    assert( status != -1 );
    printf(" Status = %d\n", status );
    
    assert( PyModule_AddObject(pModule, argv[1], m ) != -1 );
    // pModule = PyImport_ExecCodeModule( argv[1],   (PyObject *)&NoddyType );
    
    
    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, argv[2]);
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(0);
            pDict = PyDict_New() ;
            for (i = 0; i < 3 ; ++i) {
                pValue = PyInt_FromLong( i*2 );
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pDict);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                /* pValue reference stolen here: */
                PyDict_SetItemString( pDict,keys[i], pValue ) ;
            }
            PySimulinkBus = Py_BuildValue("s#",  (char* )&bus,  sizeof(SimulinkBus)) ;
            PyDict_SetItemString( pDict,"SimulinkBus", PySimulinkBus ) ;
            
            pValue = PyObject_Call(pFunc, pArgs,pDict);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyInt_AsLong(pValue));
                pValue=PyDict_GetItemString( pDict, "jack" );
                
                printf("jack is %ld, signal is %d\n", PyInt_AsLong(pValue), signal );
                
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return 1;
    }
    Py_Finalize();
    return 0;
}
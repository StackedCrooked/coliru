
/* 
   Prashant Srivastava
   Demonstration for Embedding Python with C structure passing

   gcc -o test Interpreter.c -Wall -Wextra -IC:\Python27\include -LC:\Python27\libs -lpython27 -pedantic -O2 
   drmemory -summary  -show_reachable  -- test.exe embed main
*/

#include <Python.h>

typedef struct {
    int a;
    char b;
    float c;
    double d;
    const char* e;
    int arr[4];
} SimulinkBus ;

SimulinkBus bus = { 42, 'Z', 34.981f, 22./7,"JACK", { 11,12,13,14 } };


int main(int argc, char *argv[])
{
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue, *PySimulinkBus ;
    Py_buffer view ;
    int i;
    if (argc < 3) 
    {
        fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
        return 1;
    }
    setenv("PYTHONPATH", ".", 0);
    Py_Initialize();
     
    pName = PyString_FromString(argv[1]);
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
 
    if (pModule != NULL) 
    {
        pFunc = PyObject_GetAttrString(pModule, argv[2]);
        /* pFunc is a new reference */
         
        if (pFunc && PyCallable_Check(pFunc)) 
        {

            pArgs = PyTuple_New(1);
            pDict = PyDict_New() ;
            
   
            PySimulinkBus = Py_BuildValue("s#",  (char* )&bus,  sizeof(SimulinkBus)) ;
            
            PyDict_SetItemString( pDict,"SimulinkBus", PySimulinkBus ) ;
            PyTuple_SetItem(pArgs, 0 , PySimulinkBus);
            
            pValue = PyObject_Call(pFunc, pArgs,pDict);
                        
            if (pValue != NULL) 
            {
                printf(" obj supports the buffer interface  : %d\n", PyObject_CheckBuffer( pValue ) );
                
                PyObject_GetBuffer(pValue, &view, PyBUF_SIMPLE);
                printf("Length: %ld Bytes \n", view.len );
                bus = *(SimulinkBus *)view.buf;
                
                printf( "Returned a = %d\n", bus.a );  
                printf( "Returned b = %c\n", bus.b );  
                printf( "Returned c = %f\n", bus.c );  
                printf( "Returned d = %f\n", bus.d );  
                printf( "Returned e = %s\n", bus.e );  
                
                for( i = 0; i<4; ++i )
                {
                    printf( "Returned arr[%d] = %d\n", i+1, bus.arr[i] ) ;
                }
            }
            else 
            {
                PyBuffer_Release(&view);
                Py_DECREF(pValue);
                Py_DECREF( PySimulinkBus );
                Py_DECREF(pDict);
                Py_DECREF(pArgs);
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else 
        {
            if (PyErr_Occurred())
            {
                PyErr_Print();
            }
            fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else 
    {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return 1;
    }
    
    Py_Finalize();
    return 0;
}
//foo_c.h
 #ifndef FOO_H
 #define FOO_H
 
 extern "C"
 {
   typdef int errcode;
   static const errcode ERROR_NONE = 0;
   static const errcode ERROR_UNKNOWN = 1;
   static const errcode ERROR_OUT_OF_MEMORY = 2;
   static const errcode ERROR_OVERFLOW = 3;
   const char* get_error_details(); //do NOT free() the memory
   
   struct Foo;
   typdef Foo* FooHandle;

   errcode Foo_init(FooHandle*);
   errcode Foo_bar(FooHandle handle, int* result);
 }
 
 #endif //FOO_H
 
 
 
 
 
 
 //foo_cpp.hpp
 #ifndef FOO_HPP
 #define FOO_HPP

 struct Foo {
     Foo();
     int bar();
 };
 
 #endif FOO_HPP
 
 
 
 
 

 //foo_cpp.cpp  (completely normal C++ class definition
 #include "foo_cpp.hpp"
 #include <exception>
 
 int Foo:bar() 
 {throw std::exception(); return 3;}

 Foo::Foo() {}
 
 
 
 
 
 
 


 //foo_c.cpp  (C HANDLERS)
 #include "foo_c.h"
 #include "foo_cpp.hpp"
 #include <exception>

thread_local std::string last_error_details;
 
errcode exception_to_code() {
    try {
        throw;
    } catch(const std::bad_alloc& err) {
        last_error_details = err.what();
        return ERROR_OUT_OF_MEMORY;
    } catch(const std::overflow_error& err) {
        last_error_details = err.what();
        return ERROR_OVERFLOW;
    } catch(const std::exception& err) {
        last_error_details = err.what();
        return ERROR_UNKNOWN;
    } catch(...) {
        last_error_details.clear();
        return ERROR_UNKNOWN;
    }
}

const char* get_error_details()
{return last_error_details.c_str();}

errcode Foo_init(FooHandle* p)
{
    try {
        *p = new Foo();
        return ERROR_NONE;
    } catch(...)
    {return exception_to_code();}
}

errcode Foo_bar(FooHandle handle, int* result)
{
    try {
        *result = handle->bar();
        return ERROR_NONE;
    } catch(...) //this pattern should look familiar...
    {return exception_to_code();}    
}
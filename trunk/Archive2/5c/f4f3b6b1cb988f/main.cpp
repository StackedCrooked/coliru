void rethrow_cpp_exception_as_java_exception() 
{
  try 
  {
      throw;
  }
  catch (const package::Exception& e)                             
  {                                                               
    jclass jc = env->FindClass("group/package/Exception");        
    if(jc) env->ThrowNew (jc, e.what());                          
    /* if null => NoClassDefFoundError already thrown */          
  }                                                               
  catch (const std::bad_alloc& e)                                 
  {                                                               
    /* OOM exception */                                           
    jclass jc = env->FindClass("java/lang/OutOfMemoryError");     
    if(jc) env->ThrowNew (jc, e.what());                          
  }                                                               
  catch (const std::ios_base::failure& e)                         
  {                                                               
    /* IO exception */                                            
    jclass jc = env->FindClass("java/io/IOException");            
    if(jc) env->ThrowNew (jc, e.what());                          
  }                                                               
  catch (const std::exception& e)                                 
  {                                                               
    /* unknown exception */                                       
    jclass jc = env->FindClass("java/lang/Error");               
    if(jc) env->ThrowNew (jc, e.what());                          
  }                                                               
  catch (...)                                                     
  {                                                               
    /* Oops I missed identifying this exception! */               
    jclass jc = env->FindClass("java/lang/Error");                
    if(jc) env->ThrowNew (jc, "unexpected exception");            
  }
}

    JNIEXPORT jlong JNICALL Java_group_package_class_function1
  (JNIEnv *env, jobject object, jlong value)
{
  try 
  {
    /* ... my processing ... */
    return jlong(result);
  } catch(...)
  {
    rethrow_cpp_exception_as_java_exception();
  }
  return 0;
}

JNIEXPORT jstring JNICALL Java_group_package_class_function2
  (JNIEnv *env, jobject object, jlong value)
{
  try 
  {
    /* ... my processing ... */
    jstring jstr = env->NewStringUTF("my result");
    return  jstr;
  }catch(...)
  {
    rethrow_cpp_exception_as_java_exception();
  }
  return 0;
}

JNIEXPORT void JNICALL Java_group_package_class_function3
  (JNIEnv *env, jobject object, jlong value)
{
  try 
  {
    /* ... my processing ... */
  }catch(...)
  {
    rethrow_cpp_exception_as_java_exception();
  }
}

int main() {
}
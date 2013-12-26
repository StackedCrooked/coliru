
template<class T>
T& dereference(T* ptr) {
    if (ptr)
        return *ptr;
    else
        throw_custom_null_pointer_error();
        
    return ????; //what do you suggest goes here?
}
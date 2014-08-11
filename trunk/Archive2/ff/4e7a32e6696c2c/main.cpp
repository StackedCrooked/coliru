

const char* get_error_name(int errorcode) {
    const char* str = nullptr;
    switch(errorcode) {
        case 0: str = "No error"; break;
        case 1: str = "generic error"; break;
        case 2: str = "divide by zero"; break;
        case 3: str = "invalid parameter"; break;
        /* ad-infinitum */ 
    }
    return str;
}
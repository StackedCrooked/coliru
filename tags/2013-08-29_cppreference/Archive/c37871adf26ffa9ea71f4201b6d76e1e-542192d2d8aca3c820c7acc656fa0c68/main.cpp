#include <map>


int main(){

	typedef std::map<int, const char*> error_code_tbl_t;
    error_code_tbl_t error_code_tbl = {
        { 0              , "ERR_OK" },
        { 1, "ERR_RT_OUT_OF_MEMORY" }, 
        // ...
    };

	return 0;
}
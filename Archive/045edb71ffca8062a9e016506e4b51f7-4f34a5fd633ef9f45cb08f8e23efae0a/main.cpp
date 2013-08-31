#include <sstream>
#include <iostream>

#define VOID void
typedef long THREADID;

typedef VOID (*AFUNPTR)();
struct INS {};
enum IPOINT {IPOINT_BEFORE, IPOINT_AFTER, IPOINT_ANYWHERE, IPOINT_TAKEN_BRANCH};
enum CALL_ORDER {
    CALL_ORDER_FIRST=100,      //Execute this call first. Value is 100.
    CALL_ORDER_DEFAULT=200,      //Default when IARG_CALL_ORDER is not specified. Value is 200.
    CALL_ORDER_LAST=300, 	 //Execute this call last. Value is 300.
};
enum IARG_TYPE {
    IARG_ADDRINT,      //Type: ADDRINT. Constant value (additional arg required).
    IARG_PTR, 	 //Type: "VOID *". Constant value (additional pointer arg required).
    IARG_BOOL, 	 //Type: BOOL. Constant (additional BOOL arg required).
    IARG_UINT32, 	 //Type: UINT32. Constant (additional integer arg required).
    IARG_INST_PTR, 	 //Type: ADDRINT. The address of the instrumented instruction. This value does not change at IPOINT_AFTER. This is simply shorthand for IARG_ADDRINT, INS_Address(ins).
    IARG_REG_VALUE, 	 //Type: ADDRINT for integer register. Value of a register (additional register arg required) REG: Register Object.
    IARG_THREAD_ID,      //Type: THREADID. Application thread id.
    IARG_CALL_ORDER,      //Type: CALL_ORDER. Determine order of analysis calls. See CALL_ORDER.
    // etc
    IARG_END,
};
enum REG_TYPE {
    REG_RAX
};
VOID INS_InsertCall(INS ins, IPOINT action, AFUNPTR funptr, ...) {}





struct REG_VALUE {
    IARG_TYPE arg = IARG_REG_VALUE;
    REG_TYPE reg;
    REG_VALUE(REG_TYPE r) :reg(r) {}
};
template<REG_TYPE reg_v>
struct REGISTER : REG_VALUE {
    REGISTER() : REG_VALUE(reg_v) {}
};

template<class func_type, class ...param_types>
VOID InsertCall(INS ins, IPOINT action, func_type funptr, param_types... param_values) 
{ INS_InsertCall(ins, action, (AFUNPTR)funptr, param_values..., IARG_END); }


void print_rax_and_tid(long rax, THREADID tid) {
    std::cout << rax << std::endl << tid << std::endl;
}

int main() {
    INS ins;
    
    InsertCall(ins, IPOINT_BEFORE, print_rax_and_tid, REGISTER<REG_RAX>(), IARG_THREAD_ID);
}
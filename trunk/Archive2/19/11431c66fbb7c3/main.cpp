#include <iostream>
#include <functional>
#include <cassert>

enum InstID {
  ADDInstID,
  SUBInstID,
  DIVInstID
};

/// Operation function object class
template <typename T, InstID ID>
struct Operation : public std::binary_function<T,T,T> {
    /// function call operator
    T operator()(T &lhs, T &rhs) const ;
};

/// Template specialization for ADDInstID
template <typename T>
struct Operation<T,ADDInstID> : public std::binary_function<T,T,T> {
    T operator()(T &lhs, T &rhs) const {
        return lhs + rhs;
    }
};

/// Template specialization for SUBInstID
template <typename T>
struct Operation<T,SUBInstID> : public std::binary_function<T,T,T> {
    T operator()(T &lhs, T &rhs) const {
        return lhs - rhs;
    }
};

/// Template specialization for DIVInstID
template <typename T>
struct Operation<T,DIVInstID> : public std::binary_function<T,T,T> {
    T operator()(T &lhs, T &rhs) const {
        return lhs / rhs;
    }
};

/// function wrapper for Operation
template <typename T>
inline T operate(InstID ID, T &lhs, T &rhs) {
    switch (ID) {
    case ADDInstID: return Operation<T,ADDInstID>()(lhs,rhs);
    case SUBInstID: return Operation<T,SUBInstID>()(lhs,rhs);
    case DIVInstID: return Operation<T,DIVInstID>()(lhs,rhs);
    default: assert(0 && "not implemented"); break;
    }
    /// unreachable - dummy result
    return lhs;
}



/// get operator name for testing
inline const char* op_name(InstID ID) {
    switch (ID) {
    case ADDInstID: return "+";
    case SUBInstID: return "-";
    case DIVInstID: return "/";
    default: assert(0 && "not implemented"); break;
    }
    return "";
}

/// pretty print
template<typename T>
void print(InstID id,T lhs,T rhs) {
    std::cout << lhs << op_name(id) << rhs << " = " << operate<T>(id,lhs,rhs) << std::endl;
}

int main() {
  // double
  print<double>(ADDInstID,1.5,0.5);
  print<double>(SUBInstID,1.5,0.5);
  print<double>(DIVInstID,1.5,0.5);
  // int
  print<int>(ADDInstID,4,6);
  print<int>(SUBInstID,4,6);
  print<int>(DIVInstID,4,6);
  // unsigned int
  print<unsigned int>(ADDInstID,4,6);
  print<unsigned int>(SUBInstID,4,6);
  print<unsigned int>(DIVInstID,4,6);

  return(0);
}

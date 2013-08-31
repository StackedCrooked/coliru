#include <iostream>
 
class our_string {
public:
   void reserve(std::size_t size) {}
   std::size_t size() const { return 0; }
   void append(const our_string& other) { }
};
 
std::ostream& operator<<(std::ostream& lhs, const our_string& rhs) {
   return lhs;
}
 
template<typename Derived> class ConcatenationExpressionBase {
public:
    std::size_t size() const {
        return static_cast<Derived>(this)->size();
    }
    void add_to_string(our_string& result) const {
        return static_cast<Derived>(this)->add_to_string(result);
    }
};
class ConcatenateString : public ConcatenationExpressionBase<ConcatenateString> {
public:
    ConcatenateString(const our_string* str)
        : p(str) {}
    ConcatenateString(const ConcatenateString& other)
        : p(other.p) {}
    const our_string* p;
    std::size_t size() const {
        return p->size();
    }
    void add_to_string(our_string& result) const {
        result.append(*p);
    }
};
template<typename LHS, typename RHS> class ConcatResult : public ConcatenationExpressionBase<ConcatResult<LHS, RHS>> {
public:
    ConcatResult(LHS l, RHS r)
        : lhs(l), rhs(r) {}
    ConcatResult(const ConcatResult& other)
        : lhs(other.lhs), rhs(other.rhs) {}
    LHS lhs;
    RHS rhs;
    std::size_t size() const {
        return lhs.size() + rhs.size();
    }
    void add_to_string(our_string& result) const {
        lhs.add_to_string(result);
        rhs.add_to_string(result);
    }
};
ConcatResult<ConcatenateString, ConcatenateString> operator+(const our_string& lhs, const our_string& rhs) {
    return ConcatResult<ConcatenateString, ConcatenateString>(&lhs, &rhs);
}
template<typename LHS> ConcatResult<LHS, ConcatenateString> operator+(const ConcatenationExpressionBase<LHS>& lhs, const our_string& rhs) {
    return ConcatResult<LHS, ConcatenateString>(static_cast<const LHS&>(lhs), &rhs);
}
template<typename RHS> ConcatResult<ConcatenateString, RHS> operator+(const our_string& lhs, const ConcatenationExpressionBase<RHS>& rhs) {
    return ConcatResult<ConcatenateString, RHS>(&lhs, static_cast<const RHS&>(rhs));
}
template<typename LHS, typename RHS> ConcatResult<LHS, RHS> operator+(const ConcatenationExpressionBase<LHS>& lhs, const ConcatenationExpressionBase<RHS>& rhs) {
    return ConcatResult<LHS, RHS>(static_cast<const LHS&>(lhs), static_cast<const RHS&>(rhs));
}
template<typename T> std::ostream& operator<<(std::ostream& lhs, const ConcatenationExpressionBase<T>& rhs) {
    our_string result;
    result.reserve(rhs.size());
    rhs.add_to_string(result);
    return lhs << result;
}
int main() {
   std::cout << our_string() + our_string() + our_string();
}
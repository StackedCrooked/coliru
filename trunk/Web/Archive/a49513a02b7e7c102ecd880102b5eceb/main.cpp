class CBase {};
class CDerived : public CBase {};

CBase* a = new CDerived();
CDerived* b = static_cast<CDerived*>(ptr);
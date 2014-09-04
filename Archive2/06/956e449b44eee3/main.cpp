#define UNIT_BASIC_UNIT_DEF2 (name) UNIT_BASIC_ ## name
#define UNIT_UNIT_TYPE_DEF2 (basic_type, name) UNIT_ ## basic_type ## _ ## name
#define UNIT_BASIC_UNIT_CLASS_NAME2(name) CUnit ## name
#define UNIT_UNIT_TYPE_CLASS_NAME2(basic_type, name) CUnit ## basic_type ## _ ## name

#define UNIT_BASIC_UNIT_DEF (name) UNIT_BASIC_UNIT_DEF2(name)
#define UNIT_UNIT_TYPE_DEF (basic_type, name) UNIT_UNIT_TYPE_DEF2 (basic_type, name)
#define UNIT_BASIC_UNIT_CLASS_NAME(name) UNIT_BASIC_UNIT_CLASS_NAME2(name)
#define UNIT_UNIT_TYPE_CLASS_NAME(basic_type, name) UNIT_UNIT_TYPE_CLASS_NAME2(basic_type, name)

#define UNIT_IMPLEMENT_UNIT_TYPE(basic_type, name) \
CUnitAbstract& UNIT_UNIT_TYPE_CLASS_NAME(basic_type, name)::dup(){\
UNIT_UNIT_TYPE_CLASS_NAME(basic_type, name) * n = new UNIT_UNIT_TYPE_CLASS_NAME(basic_type, name)(this->value);\
return *n;\
}\
CUnitAbstract& UNIT_UNIT_TYPE_CLASS_NAME(basic_type, name) ::operator+(CUnitAbstract& value){\
DYNAMIC_ASSERT(dynamic_cast< UNIT_BASIC_UNIT_CLASS_NAME(basic_type) *>(&value) != NULL);\
CUnitAbstract * tmp = &this->dup();\
*tmp = this->value + conversionTable[UNIT_BASIC_UNIT_DEF(basic_type)][UNIT_UNIT_TYPE_DEF(basic_type, name)] * value.getInBasicUnit();return *tmp;\
}

class CUnitAbstract {};
UNIT_IMPLEMENT_UNIT_TYPE(DISTANCE, METER)

int main() {
    return 0;
}
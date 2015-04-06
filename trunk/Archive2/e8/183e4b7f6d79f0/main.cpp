#include <iostream>

using Function_Pointer_Type = void (*)(void);
struct Table_Entry
{
  char const * data_type_name;
  Function_Pointer_Type data_type_function;
};

void Process_Int(void) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
void Process_Double(void) { std::cout << __PRETTY_FUNCTION__ << "\n"; }

static const Table_Entry data_type_function_table[] =
{
  {"int", Process_Int},
  {"double", Process_Double},
};

int main()
{
    using std::begin; using std::end; using std::find_if;
    auto& table = data_type_function_table;
    
    auto const s = "int";
    auto const i = find_if(begin(table), end(table), [&](Table_Entry const& e) { return e.data_type_name == s; });
    if(i != end(table)) i->data_type_function();
}
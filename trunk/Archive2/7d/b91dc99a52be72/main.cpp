
// Cutting some slack with regard to macro naming rules
//
//                   StackedCrooked
//
// Macros suffer from two problems:
// (1) macros are bad
// (2) ALL_UPPERCASE is ugly
//
//
// In order to improve the sitation I propose softening of the naming rules:
//
//
// Pattern "company_library_action"
#define boost_utils_log(msg)
    // Name components:
    // - "boost" is the company namespace (master namespace)
    // - "utils" is a subnamespace
    // - "log" is the action name\


// Pattern "library_action"
#define utils_log(msg)
    // Restrictions:
    // - use inside its namespace only
    // - undef when done or at end of file
    // - internal use only (not accessible for outsiders)


// Pattern: short lower-case action name
#define log(msg) ...
    // - use in small scopes
    // - undef when done

    
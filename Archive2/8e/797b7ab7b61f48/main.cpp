// List of exceptions. Extend (only) if needed.
//
// THE RULES
// =========
// - Exceptions from this list will be rethrown as a corresponding API exception
//   at the client side.

// - You may throw exceptions from this list from inside the Communication code
//   or StackController code.
//
// - Exceptions that are thrown from the lower-layer code (e.g. the
//   protocolstack, address library, boost, stl, ...) must be remapped to one
//   of the exception types from this list.
//
// - A global mapping is set on the RPC Server object (bbserver.cpp)
// - The global mapping takes care of almost all exceptions.
//
// - The RPC command implementations should not define a try-catch block unless
//   for very specific cases which can not be handled by the global mapper.
//   This makes exception handling more consistent and does not pollute the
//   RPC code with multiple catch blocks for each command implementation.
//
// - These are "umbrella" exceptions. For example:
//     BadIPAddress is used for both IPv4 and IPv6
//     DHCPFailed covers both DHCPv4 and DHCPv6
//     AddressResolutionFailed covers both ARP and NeighborSolication.
//     etc...
//   This reduces the number of exception types and simplifies exception
//   handling for us and the user.
//
// - At the client side, TechnicalError should only be caught in a top-level
//   catch block which prints a general message of apology and logs the detailed
//   error message for debugging puposes. The detailed error message should
//   probably not be shown to the user because it is only useful for developers.
//
// - Clients usually want to catch ConfigError or InitializationError.
//   They could also catch DomainError (which covers both).
//
// - ConfigErrors indicate errors in the user program. They are often "fatal"
//   because a scenario cannot start if config is invalid.

// - InitializationErrors indicate network errors. It's up to the user to
//   decide whether to proceed or not.
//
// - We should keep this list of exceptions to a minimum. If we define too many
//   types then it will not be obvious for a user which one he needs to catch.
//
// NOTE: Private exceptions which derive public exceptions. This enables us to
//       have more specific error messages without having to expose a new
//       public exception type.
//
#define COMMUNICATION_EXCEPTIONS_LIST(X) \
\
    /*====================================================*/ \
    /*=             COMMUNICATION EXCEPTIONS             =*/ \
    /*====================================================*/ \
    X( TechnicalError              , Exception             ) \
    X( DomainError                 , Exception             ) \
    /*----------------------------------------------------*/ \
    X( ConfigError                 , DomainError           ) \
    X( InitializationError         , DomainError           ) \
    /*----------------------------------------------------*/ \
    X( BadIPAddress                , ConfigError           ) \
    X( BadMACAddress               , ConfigError           ) \
    X( IncompleteConfig            , ConfigError           ) \
    X( InvalidConfig               , ConfigError           ) \
    X( UnsupportedConfig           , ConfigError           ) \
    X( NotAllowed                  , ConfigError           ) \
    X( PortNumberAlreadyUsed       , ConfigError           ) \
    X( SessionAlreadyExists        , ConfigError           ) \
    X( ConfigAttemptedDuringRun    , ConfigError           ) \
    X( HTTPRestartNotAllowed       , ConfigError           ) \
    X( DuplicateAddressDetected    , ConfigError           ) \
    X( SessionUnavailable          , ConfigError           ) \
    X( InvalidRequestSize          , ConfigError           ) \
    X( InvalidRequestURI           , ConfigError           ) \
    X( InvalidCongestionAvoider    , ConfigError           ) \
    X( OutOfResources              , ConfigError           ) \
    X( BadFilter                   , ConfigError           ) \
    /*----------------------------------------------------*/ \
    X( AddressResolutionFailed     , InitializationError   ) \
    X( DHCPFailed                  , InitializationError   ) \
    X( RouterRequired              , InitializationError   ) \
    X( RouterSolicitationFailed    , InitializationError   ) \
    X( TCPConnectionTimout         , InitializationError   ) \
    /*====================================================*/


// X-macro for generating exception class.
// The name X is used for convention, you could use another name too.
#define X(Name, Base) \
    struct Name : Base { \
        Name() : Base() { appendName(#Name); } \
        template<typename T> Name(const T& t) : Base(t) { appendName(#Name); } \
    };

// apply the X-macro to the list of exceptions
// this generates the exception classes
COMMUNICATION_EXCEPTIONS_LIST(X)

// undef the X-macro to avoid name pollution
#undef X


#define COMMUNICATION_THROW(Name) \
    LOG(Warning) << __FILE__ << ":" << __LINE__ << " throw " << #Name; \
    throw Name()
    

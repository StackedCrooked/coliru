

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
    X( NotAllowed                  , ConfigError           ) \
    X( DuplicateAddressDetected    , ConfigError           ) \
    X( HTTPSessionNotFound         , ConfigError           ) \
    X( InvalidRequestURI           , ConfigError           ) \
    X( InvalidCongestionAvoider    , ConfigError           ) \
    /*----------------------------------------------------*/ \
    X( AddressResolutionFailed     , InitializationError   ) \
    X( DHCPFailed                  , InitializationError   ) \
    X( RouterRequired              , InitializationError   ) \
    X( RouterSolicitationFailed    , InitializationError   ) \
    X( TCPConnectionTimout         , InitializationError   ) \
    /*====================================================*/
    
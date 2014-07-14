#if defined(TESTING) 
   #if (TESTING == UNIT_TEST)
            State<StateTypeEnum, EventTypeEnum>::_isIgnoredEvent = false;
            State<StateTypeEnum, EventTypeEnum>::_isInvalidEvent = false;
   #endif
#endif
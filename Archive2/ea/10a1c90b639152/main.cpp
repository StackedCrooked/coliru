struct encoder_t {
    
} const encoder = {};

struct validator_t {
    
} const validator = {};

struct test {
// none of these work
#if 0
    // This says it can't deduce the types, so it's understandable
    // that it doesn't work (albeit I wish it could deduce back into the type signature)
    template <typename Range, typename Encoding, typename Validation>
    test ( Range&& range, Encoding&& encoding = encoder, Validation&& validation = validator ) {
        
    }
#elif 0
    // I can default the type now, since that was the error from the above,
    // but now it complains that the type provided doesn't match
    // the type for the encoder
    template <typename Range, typename Encoding = encoder_t, typename Validation = validator_t>
    test ( Range&& range, Encoding&& encoding = encoder, Validation&& validation = validator ) {
        
    }
#elif 1
    // okay, so let's try decltype...
    // but now it doesn't work because it can't bind an lvalue to the actual type here! ( const type&& <-- wat )
    template <typename Range, typename Encoding = decltype( encoder ), typename Validation = decltype( validator )>
    test ( Range&& range, Encoding&& encoding = encoder, Validation&& validation = validator ) {
        
    }
#else
    // Works! But the syntax is strange... potential ramifications/deduction mishaps?
    // Is this the "proper" way to default these arguments?
    template <typename Range, typename Encoding = encoder_t, typename Validation = validator_t>
    test ( Range&& range, Encoding&& encoding = Encoding(), Validation&& validation = Validation() ) {
        
    }
#endif

};

int main() {
    
    test( "woof" );
    
}
struct encoder_t {
    
} const encoder = {};

struct validator_t {
    
} const validator = {};

struct test {
    
    template <typename Range, typename Encoding, typename Validation>
    test ( Range&& range, Encoding&& encoding = encoder, Validation&& validation = validator ) {
        
    }
    
};

int main() {
    
    test( "woof" );
    
}
// what's more readable?

int main() {
    bool looping = true;
    bool playing = true;
    
    // this
    if(!looping) {
        playing = false;
    }
    
    // vs
    
    playing = looping;
}
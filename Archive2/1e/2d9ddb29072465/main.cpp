// what's more readable?

int main() {
    bool looping = true;
    bool playing = true;
    String muhDick = "Huuuuuuuuuuuuuuuuuge";
    
    // this
    if(!looping) {
        playing = false;
    }
    
    // vs
    
    playing = looping;
}
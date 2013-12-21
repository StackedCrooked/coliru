enum class Drawing {Line, Square, Triangle};


Drawing analyzeStuff(){
    Drawing theDrawing; //This is fine. 
    if(true)
        theDrawing = Drawing::Line; //This brings up an error.
    //...Other else-ifs using the same thing.
    return theDrawing; //This is also fine.
}

int main() {}
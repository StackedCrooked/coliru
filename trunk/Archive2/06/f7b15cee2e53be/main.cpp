#include <utility>

class Image
{
    Image() = default;
    Image(const char*) {}
};

Image threshold(Image&& img){
    //will be called for rvalues
    //do something here that alters the image
    return img;
}

Image threshold(Image img){
    //this will be called for lvalues.
    //now we have a local copy of img so we can forward it as rvalue to the other one
    img = threshold(std::move(img));
    return img;
}

Image functionThatReturnsImage() { return Image(); }

int main(){
    Image img("filename.png");
    Image img2;
    //here the lvalue function will be called
    img2 = threshold(img);

    //here the rvalue function should be called
    Image img3 = threshold(functionThatReturnsImage());
}
}
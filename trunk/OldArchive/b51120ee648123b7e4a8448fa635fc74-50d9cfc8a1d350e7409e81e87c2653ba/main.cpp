static const struct clone_tag_t{} clone_tag{};

class Shape{
public:
    Shape() = default;
    Shape(Shape const&) = delete;
    Shape(Shape&&) = delete;
    Shape& operator=(Shape const&) = delete;
    Shape& operator=(Shape&&) = delete;
    // use a smart pointer here, just raw for demonstration
    virtual Shape* clone() const = 0;

protected:
    Shape(clone_tag_t, Shape const& other){}
};

class Circle : public Shape{
public:
    Circle() = default;
    
    Shape* clone() const{ return new Circle(clone_tag, *this); }
  
protected:
    Circle(clone_tag_t, Circle const& other)
      : Shape(clone_tag, other) {}
};

int main(){
    Shape* c = new Circle();
    Shape* s = c->clone();
}
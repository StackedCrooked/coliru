class FeetInches
{
private:
   int feet;        // To hold a number of feet
   int inches;      // To hold a number of inches

public:
   // Constructor
    FeetInches(int f = 0, int i = 0)
        { feet = f;
          inches = i; }

   // Mutator functions
    void setFeet(int f)
        { feet = f; }

    void setInches(int i)
        { inches = i; }

   // Accessor functions
    int getFeet() const
        { return feet; }

    int getInches() const
        { return inches; }

};

class RoomDimension
{
private:

    FeetInches length;
    FeetInches width;

public:

    // constructors
    RoomDimension(void);

    // getter functions
    FeetInches getLength(void) const
    { return length; }

    FeetInches getWidth(void) const
    { return width; }

    // setter functions
    void setLength(FeetInches l)
    { length = l; }

    void setWidth(FeetInches w)
    { width = w; }

};
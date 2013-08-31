FloatColor (byte grey);

FloatColor (byte grey, byte alpha);

FloatColor (byte red, byte green, byte blue);

FloatColor (byte red, byte green, byte blue, byte alpha);

// Delegates to the `byte` one, since FloatColor{ 255 } would throw a coniption between `float` and `byte`.
FloatColor (int grey);

FloatColor (int grey, int alpha);

FloatColor (int red, int green, int blue);

FloatColor (int red, int green, int blue, int alpha);

FloatColor (float grey);

FloatColor (float grey, float alpha);

FloatColor (float red, float green, float blue);

FloatColor (float red, float green, float blue, float alpha);
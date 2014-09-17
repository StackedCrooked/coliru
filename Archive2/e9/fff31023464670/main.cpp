#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

class Terminal
{
    int xpos;
    int ypos;
    volatile uint16_t video_buffer;
    
public:
    enum class Color
    {
        Black        = 0,
    	Blue         = 1,
    	Green        = 2,
    	Cyan         = 3,
    	Red          = 4,
    	Magenta      = 5,
    	Brown        = 6,
    	LightGrey    = 7,
    	DarkGrey     = 8,
    	LightBlue    = 9,
    	LightGreen   = 10,
    	LightCyan    = 11,
    	LightRed     = 12,
    	LightMagenta = 13,
    	LightBrown   = 14,
    	White        = 15,
    };
    
    void clrscr();
    
    void putch(int c);
    
    void puts(const char* s);

    uint8_t make_color(Color fg, Color bg);
    
    uint16_t make_vgaentry(char c, uint8_t color);
};

/*
+-------+------------------+------------------+
| Blink | Background Color | Foreground Color |
+-------+------------------+------------------+
|     7 | 6 5 4            | 3 2 1 0          |
+-------+------------------+------------------+
*/

uint8_t Terminal::make_color(Terminal::Color fg, Terminal::Color bg)
{
    printf("%08x", static_cast<uint8_t>(fg));
    return static_cast<uint8_t>(fg) | 
           static_cast<uint8_t>(bg) << 4;
}

uint16_t Terminal::make_vgaentry(char c, uint8_t color)
{
    uint16_t c16 = c;
    uint16_t color16 = color;
    return c16 | color16 << 8;
}
    
int main()
{
    Terminal terminal;
    terminal.make_color(Terminal::Color::White, Terminal::Color::Black);
    return 0;
}

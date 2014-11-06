/*
The MIT License (MIT)

Copyright (c) 2014 Johann Gerell

Permission is hereby granted, free of charge, to any person obtaining a copy
        of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

        The above copyright notice and this permission notice shall be included in all
        copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <locale>
#include <codecvt>
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <iterator>

template <typename T>
struct code_unit_t
{
    T value;

    code_unit_t(T value)
        : value(value)
    {
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const code_unit_t<T>& code_unit)
{
    stream
        << "0x"
        << std::hex
        << std::uppercase
        << std::setw(2 * sizeof(code_unit.value))
        << std::setfill('0')
        << static_cast<int64_t>(code_unit.value);

    return stream;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<code_unit_t<T>>& code_units)
{
    std::copy(std::begin(code_units),
              std::end(code_units),
              std::ostream_iterator<code_unit_t<T>>(stream, " "));
            
    return stream;
}

struct raw_t
{
    std::string  utf8;
    std::wstring utf16;

    raw_t(std::string utf8, std::wstring utf16)
        : utf8(utf8)
        , utf16(utf16)
    {
    }
};

struct converted_t
{
    std::string  utf8;
    std::wstring utf16;

    converted_t(raw_t raw)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        utf8  = converter.to_bytes(raw.utf16);
        utf16 = converter.from_bytes(raw.utf8);
    }
};

struct code_units_t
{
    std::vector<code_unit_t<uint8_t>>  utf8;
    std::vector<code_unit_t<uint16_t>> utf16;

    code_units_t(converted_t converted)
    {
        std::copy(std::begin(converted.utf8),
                  std::end(converted.utf8),
                  std::back_inserter(utf8));

        std::copy(std::begin(converted.utf16),
                  std::end(converted.utf16),
                  std::back_inserter(utf16));
    }
};

template <typename T>
struct result_t
{
    bool                        succeeded;
    std::vector<code_unit_t<T>> code_units;

    result_t(bool succeeded, std::vector<code_unit_t<T>> code_units)
        : succeeded(succeeded)
        , code_units(code_units)
    {
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const result_t<T>& result)
{
    stream
            << std::dec
            << std::boolalpha
            << "\tsucceeded       : " << result.succeeded << "\n"
            << "\tcode unit count : " << result.code_units.size() << "\n"
            << "\tcode units      : " << result.code_units << "\n";

    return stream;
}

int main()
{
    // 1. Go to http://rishida.net/tools/conversion/
    // 2. Paste おはよう into the "Mixed input" text input field
    // 3. Use the values from the "UTF-8/16 code units" text output fields
    const char*        raw_utf8   { "\xE3\x81\x8A\xE3\x81\xAF\xE3\x82\x88\xE3\x81\x86" };
    const wchar_t*     raw_utf16  { L"\x304A\x306F\x3088\x3046" };
    const raw_t        raw        { raw_utf8, raw_utf16 };
    const converted_t  converted  { raw };
    const code_units_t code_units { converted };

    std::cout
        << "UTF-16 => UTF-8" << "\n"
        << result_t<uint8_t>(raw.utf8  == converted.utf8,  code_units.utf8) << "\n"
        << "UTF-8 => UTF-16" << "\n"
        << result_t<uint16_t>(raw.utf16 == converted.utf16, code_units.utf16) << "\n";

    return 0;
}
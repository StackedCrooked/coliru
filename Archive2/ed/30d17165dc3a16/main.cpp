#include <iostream>
#include <sstream>
#include <bitset>
#include <iomanip>

enum FileFormatBits {
    RecsFixed    = 1,           // Fixed-width records
    RecsLine     = 1<<1,        // Newline-terminated records
    RecsBlock    = 1<<2,        // Blocked records
    RecsAuto     = 1<<3,        // Auto-detect Line vs Block vs Fixed
    RecsXML      = 1<<4,        // XML records
    RecsAll      = (RecsXML << 1) - RecsFixed,

    FieldsFixed  = 1<<8,        // Fixed-width fields
    FieldsTab    = 1<<9,        // Tab-separated fields
    FieldsXML    = 1<<10,       // XML fields
    FieldsKey    = 1<<11,       // Record keys
    FieldsAll    = (FieldsKey << 1) - FieldsFixed,

    CharASCII    = 1<<5,        // ASCII
    CharEBCDIC   = 1<<6,        // EBCDIC
    CharAuto     = 1<<7,        // Autodetect ASCII vs EBCDIC
    CharAll      = (CharAuto << 1) - CharASCII,

    EditMask     = (7 << 15),   // 3 bits are assigned to edit values
    EditNormal   = (0 << 15),   // Field that's normally editable
    EditIdentity = (1 << 15),   // Field that's part of the RKEY
    EditAuto     = (2 << 15),   // Field auto-set (by RFD) in update records
    EditInternal = (3 << 15),   // Field used only by ITA
    EditViewOnly = (4 << 15),   // Field that should be viewable but not editable
    EditUpdate   = (5 << 15),   // Field used only when applying updates

    UnusedBit0   = 1<<18,
    UnusedBit1   = 1<<19,

    PrintXMLHdr    = 1 << 20,
    PrintXMLLine   = 1 << 21,
    PrintByteTable = 1 << 22,     // Output an ATPCo/QPX byte mapping table
};

enum FileFormat { // Accepted by QPXRecReader as file formats.
    LineTab             = (RecsLine     | FieldsTab             | CharASCII),
    LineATP             = (RecsLine     | FieldsFixed           | CharASCII),
    AutoATP             = (RecsAuto     | FieldsFixed           | CharAuto),
    AutoATPASC          = (RecsAuto     | FieldsFixed           | CharASCII),
    // NOTE: for fixed format (Fixed* -- or Auto* autodetecting fixed), you need to specify the
    // fixed_width field (to be nonzero).
    FixedATP            = (RecsFixed    | FieldsFixed           | CharAuto),
    FixedATPASC         = (RecsFixed    | FieldsFixed           | CharASCII),
    FixedATPEBC         = (RecsFixed    | FieldsFixed           | CharEBCDIC),
    BlockATP            = (RecsBlock    | FieldsFixed           | CharAuto),
    BlockATPASC         = (RecsBlock    | FieldsFixed           | CharASCII),
    BlockATPEBC         = (RecsBlock    | FieldsFixed           | CharEBCDIC),
    ShortXML            = (RecsXML      | FieldsXML             | CharASCII),
    ShortKeyedXML       = (RecsXML      | (FieldsXML|FieldsKey) | CharASCII),
    XML                 = (RecsXML      | FieldsXML             | CharASCII | (PrintXMLHdr | PrintXMLLine)),
    KeyedXML            = (RecsXML      | (FieldsXML|FieldsKey) | CharASCII | (PrintXMLHdr | PrintXMLLine)),
    SplicedXML          = (RecsXML      | FieldsXML             | CharASCII | PrintXMLLine),
    SplicedKeyedXML     = (RecsXML      | (FieldsXML|FieldsKey) | CharASCII | PrintXMLLine),
    ByteTable           = (RecsAll      | (FieldsXML|FieldsFixed|FieldsTab) | CharASCII | PrintByteTable),
    KeyedByteTable      = (RecsAll      | FieldsAll             | CharASCII | PrintByteTable)
};

bool matchesFileFormat(int match_bits, int file_format) {
    int bits = ((match_bits < 0) ? -match_bits : match_bits) & FieldsAll;
    return ((match_bits <= 0 || (bits & file_format) == bits) &&
            (match_bits >= 0 || (bits & file_format) == 0));
}
void dump_matches(const char* match_bits_label, const char* file_format_label, int match_bits, int file_format) {
    std::cout << std::setfill(' ') << std::left << std::setw(15) << match_bits_label << " ";
    std::cout << std::setfill(' ') << std::internal << std::setw(20) << (matchesFileFormat(match_bits, file_format) ? " does match " : " does not match ");
    std::cout << std::setfill(' ') << std::right << std::setw(15) << file_format_label;
    std::cout << std::endl;
}

void dump_flag(const char* label, int value) {
    std::cout << std::setfill(' ') << std::left << std::setw(25) << label << " ";
    std::cout << std::bitset<32>(value).to_string('-', 'X') << "    ";
    std::cout << "0x" << std::hex << std::right << std::setfill('0') << std::setw(8) << value;
    std::cout << std::endl;
}

#define D(expr) dump_flag(#expr, expr)
#define M(match_bits, file_format) dump_matches(#match_bits, #file_format, match_bits, file_format)
int main()
{
    {
    D(RecsFixed);
    D(RecsLine);
    D(RecsBlock);
    D(RecsAuto);
    D(RecsXML);
    D(RecsAll);
    std::cout << std::endl;
    }

    {
    D(FieldsFixed);
    D(FieldsTab);
    D(FieldsXML);
    D(FieldsKey);
    D(FieldsAll);
    std::cout << std::endl;
    }
    
    {
    D(CharASCII);
    D(CharEBCDIC);
    D(CharAuto);
    D(CharAll);
    std::cout << std::endl;
    }
    
    {
    D(EditMask);
    D(EditNormal);
    D(EditIdentity);
    D(EditAuto);
    D(EditInternal);
    D(EditViewOnly);
    D(EditUpdate);
    std::cout << std::endl;
    }
    
    {
    D(UnusedBit0);
    D(UnusedBit1);
    std::cout << std::endl;
    }
    
    {
    D(PrintXMLHdr);
    D(PrintXMLLine);
    D(PrintByteTable);
    std::cout << std::endl;
    }
    
    D(FieldsXML);
    D(+FieldsXML);
    D(-FieldsXML);
    D(-(-FieldsXML) & FieldsAll);
    D(ByteTable & FieldsAll);
    
    D(ByteTable);
    D(ByteTable ^ FieldsXML);
    std::cout << std::endl;
    
    {
    D(LineTab);
    D(LineATP);
    D(AutoATP);
    D(AutoATPASC);
    D(FixedATP);
    D(FixedATPASC);
    D(FixedATPEBC);
    D(BlockATP);
    D(BlockATPASC);
    D(BlockATPEBC);
    D(ShortXML);
    D(ShortKeyedXML);
    D(XML);
    D(KeyedXML);
    D(SplicedXML);
    D(SplicedKeyedXML);
    D(ByteTable);
    D(KeyedByteTable);
    }
    std::cout << std::endl;
    
    {
        M(-FieldsXML, FieldsXML);
        M(-FieldsXML, FieldsFixed);
    }
}
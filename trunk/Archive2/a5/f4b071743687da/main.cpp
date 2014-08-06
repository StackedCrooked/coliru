#include <iostream>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;
//by filo NO UTF8!!!
static std::map<string, string> HTML_ENTITIES_MAP;
bool HTML_ENTITIES_MAP_INIT = false;
static void initialize_html_entities_map(){

    HTML_ENTITIES_MAP.insert ( std::pair<string,string>("AElig", "Æ" ) );
    HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Aacute", "Á" ) );
    HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Acirc", "Â" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Agrave", "À" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Alpha", "Α" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Aring", "Å" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Atilde", "Ã" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Auml", "Ä" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Beta", "Β" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Ccedil", "Ç" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Chi", "Χ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Dagger", "‡" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Delta", "Δ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ETH", "Ð" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Eacute", "É" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Ecirc", "Ê" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Egrave", "È" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Epsilon", "Ε" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Eta", "Η" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Euml", "Ë" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Gamma", "Γ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Iacute", "Í" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Icirc", "Î" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Igrave", "Ì" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Iota", "Ι" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Iuml", "Ï" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Kappa", "Κ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Lambda", "Λ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Mu", "Μ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Ntilde", "Ñ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Nu", "Ν" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "OElig", "Œ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Oacute", "Ó" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Ocirc", "Ô" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Ograve", "Ò" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Omega", "Ω" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Omicron", "Ο" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Oslash", "Ø" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Otilde", "Õ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Ouml", "Ö" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Phi", "Φ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Pi", "Π" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Prime", "″" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Psi", "Ψ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Rho", "Ρ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Scaron", "Š" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Sigma", "Σ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "THORN", "Þ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Tau", "Τ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Theta", "Θ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Uacute", "Ú" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Ucirc", "Û" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Ugrave", "Ù" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Upsilon", "Υ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Uuml", "Ü" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Xi", "Ξ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Yacute", "Ý" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Yuml", "Ÿ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "Zeta", "Ζ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "aacute", "á" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "acirc", "â" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "acute", "´" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "aelig", "æ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "agrave", "à" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "alefsym", "ℵ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "alpha", "α" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "amp", "&" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "and", "∧" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ang", "∠" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "apos", "'" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "aring", "å" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "asymp", "≈" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "atilde", "ã" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "auml", "ä" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "bdquo", "„" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "beta", "β" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "brvbar", "¦" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "bull", "•" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "cap", "∩" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ccedil", "ç" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "cedil", "¸" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "cent", "¢" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "chi", "χ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "circ", "ˆ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "clubs", "♣" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "cong", "≅" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "copy", "©" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "crarr", "↵" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "cup", "∪" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "curren", "¤" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "dArr", "⇓" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "dagger", "†" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "darr", "↓" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "deg", "°" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "delta", "δ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "diams", "♦" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "divide", "÷" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "eacute", "é" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ecirc", "ê" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "egrave", "è" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "empty", "∅" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "emsp", " " ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ensp", " " ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "epsilon", "ε" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "equiv", "≡" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "eta", "η" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "eth", "ð" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "euml", "ë" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "euro", "€" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "exist", "∃" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "fnof", "ƒ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "forall", "∀" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "frac12", "½" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "frac14", "¼" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "frac34", "¾" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "frasl", "⁄" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "gamma", "γ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ge", "≥" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "gt", ">" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "hArr", "⇔" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "harr", "↔" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "hearts", "♥" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "hellip", "…" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "iacute", "í" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "icirc", "î" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "iexcl", "¡" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "igrave", "ì" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "image", "ℑ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "infin", "∞" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "int", "∫" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "iota", "ι" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "iquest", "¿" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "isin", "∈" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "iuml", "ï" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "kappa", "κ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "lArr", "⇐" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "lambda", "λ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "lang", "〈" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "laquo", "«" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "larr", "←" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "lceil", "⌈" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ldquo", "“" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "le", "≤" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "lfloor", "⌊" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "lowast", "∗" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "loz", "◊" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "lrm", "\xE2\x80\x8E" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "lsaquo", "‹" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "lsquo", "‘" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "lt", "<" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "macr", "¯" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "mdash", "—" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "micro", "µ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "middot", "·" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "minus", "−" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "mu", "μ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "nabla", "∇" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "nbsp", " " ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ndash", "–" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ne", "≠" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ni", "∋" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "not", "¬" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "notin", "∉" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "nsub", "⊄" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ntilde", "ñ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "nu", "ν" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "oacute", "ó" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ocirc", "ô" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "oelig", "œ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ograve", "ò" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "oline", "‾" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "omega", "ω" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "omicron", "ο" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "oplus", "⊕" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "or", "∨" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ordf", "ª" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ordm", "º" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "oslash", "ø" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "otilde", "õ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "otimes", "⊗" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ouml", "ö" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "para", "¶" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "part", "∂" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "permil", "‰" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "perp", "⊥" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "phi", "φ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "pi", "π" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "piv", "ϖ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "plusmn", "±" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "pound", "£" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "prime", "′" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "prod", "∏" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "prop", "∝" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "psi", "ψ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "quot", "\"" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "rArr", "⇒" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "radic", "√" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "rang", "〉" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "raquo", "»" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "rarr", "→" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "rceil", "⌉" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "rdquo", "”" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "real", "ℜ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "reg", "®" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "rfloor", "⌋" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "rho", "ρ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "rlm", "\xE2\x80\x8F" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "rsaquo", "›" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "rsquo", "’" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "sbquo", "‚" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "scaron", "š" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "sdot", "⋅" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "sect", "§" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "shy", "\xC2\xAD" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "sigma", "σ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "sigmaf", "ς" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "sim", "∼" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "spades", "♠" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "sub", "⊂" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "sube", "⊆" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "sum", "∑" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "sup", "⊃" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "sup1", "¹" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "sup2", "²" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "sup3", "³" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "supe", "⊇" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "szlig", "ß" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "tau", "τ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "there4", "∴" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "theta", "θ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "thetasym", "ϑ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "thinsp", " " ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "thorn", "þ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "tilde", "˜" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "times", "×" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "trade", "™" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "uArr", "⇑" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "uacute", "ú" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "uarr", "↑" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ucirc", "û" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "ugrave", "ù" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "uml", "¨" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "upsih", "ϒ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "upsilon", "υ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "uuml", "ü" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "weierp", "℘" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "xi", "ξ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "yacute", "ý" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "yen", "¥" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "yuml", "ÿ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "zeta", "ζ" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "zwj", "\xE2\x80\x8D" ) );
	HTML_ENTITIES_MAP.insert ( std::pair<string,string>( "zwnj", "\xE2\x80\x8C" ) );
	
	HTML_ENTITIES_MAP_INIT = true;
}

int reverse_bits_recursive(unsigned int num, unsigned int numBits)
{
    unsigned int reversedNum;;
    unsigned int mask = 0;

    mask = (0x1 << (numBits/2)) - 1;

    if (numBits == 1) return num;
    reversedNum = reverse_bits_recursive(num >> numBits/2, numBits/2) |
                   reverse_bits_recursive((num & mask), numBits/2) << numBits/2;
    return reversedNum;
}

string decode_html_entities(string src)
{
    if(!HTML_ENTITIES_MAP_INIT)
    	initialize_html_entities_map();
	stringstream ss;
    size_t curr_end = 0;
    int current_save = 0;
	for(size_t current = -1; (current = src.find("&", current+1))!=std::string::npos ; )
		{
			curr_end = src.find(";", current+1);
            if(curr_end == std::string::npos){
                break;
            }
			size_t next_curr = src.rfind("&", curr_end-1);
			if(next_curr != std::string::npos && next_curr > current && next_curr < curr_end){
				//cout<<next_curr<<" ";
                //continue;
                current = next_curr;
			}
            if(current>0)
                ss<<src.substr(current_save, current-current_save);
            current_save = curr_end+1;
            string a = src.substr(current+1, curr_end-current-1);
            //cout<<src[current]<<"-"<<src[curr_end] <<" sub:"<<a;
            
            bool found = false;
            if(a[0] == '#'){
                //fottesega dei caratteri &#nnn; semplicemente lo cancello
                int numb;
                std::istringstream(a.substr(1)) >> numb;
                if(numb<256){
                //    cout << numb << (char)numb <<" ";
                    ss << (char)numb;
                } else {
                    ss << (reverse_bits_recursive(numb,8) & 0xff); 
                }
                cout<<"FFFFFFF";
                found = true;
            } else {
                auto find = HTML_ENTITIES_MAP.find(a);
                if(find != HTML_ENTITIES_MAP.end()){
					//cout << find->first << " becomes " << find->second<<endl;
                    ss << find->second;
                    found = true;
                }
            }
            if(!found){
                ss<<"&"<<a<<";";
            }
		}
    ss<<src.substr(current_save);
	return ss.str();
}


/* MD5
 converted to C++ class by Frank Thilo (thilo@unix-ag.org)
 for bzflag (http://www.bzflag.org)
 
   based on:
 
   md5.h and md5.c
   reference implementation of RFC 1321
 
   Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.
 
License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.
 
License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.
 
RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.
 
These notices must be retained in any copies of any part of this
documentation and/or software.
 
*/
 
#ifndef BZF_MD5_H
#define BZF_MD5_H
 
#include <cstring>
#include <iostream>
 
 
// a small class for calculating MD5 hashes of strings or byte arrays
// it is not meant to be fast or secure
//
// usage: 1) feed it blocks of uchars with update()
//      2) finalize()
//      3) get hexdigest() string
//      or
//      MD5(std::string).hexdigest()
//
// assumes that char is 8 bit and int is 32 bit
class MD5
{
public:
  typedef unsigned int size_type; // must be 32bit
 
  MD5();
  MD5(const std::string& text);
  void update(const unsigned char *buf, size_type length);
  void update(const char *buf, size_type length);
  MD5& finalize();
  std::string hexdigest() const;
  friend std::ostream& operator<<(std::ostream&, MD5 md5);
 
private:
  void init();
  typedef unsigned char uint1; //  8bit
  typedef unsigned int uint4;  // 32bit
  enum {blocksize = 64}; // VC6 won't eat a const static int here
 
  void transform(const uint1 block[blocksize]);
  static void decode(uint4 output[], const uint1 input[], size_type len);
  static void encode(uint1 output[], const uint4 input[], size_type len);
 
  bool finalized;
  uint1 buffer[blocksize]; // bytes that didn't fit in last 64 byte chunk
  uint4 count[2];   // 64bit counter for number of bits (lo, hi)
  uint4 state[4];   // digest so far
  uint1 digest[16]; // the result
 
  // low level logic operations
  static inline uint4 F(uint4 x, uint4 y, uint4 z);
  static inline uint4 G(uint4 x, uint4 y, uint4 z);
  static inline uint4 H(uint4 x, uint4 y, uint4 z);
  static inline uint4 I(uint4 x, uint4 y, uint4 z);
  static inline uint4 rotate_left(uint4 x, int n);
  static inline void FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
  static inline void GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
  static inline void HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
  static inline void II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
};
 
std::string md5(const std::string str);
 
#endif

#include <cstdio>
 
 
// Constants for MD5Transform routine.
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21
 
///////////////////////////////////////////////
 
// F, G, H and I are basic MD5 functions.
inline MD5::uint4 MD5::F(uint4 x, uint4 y, uint4 z) {
  return (x&y) | (~x&z);
}
 
inline MD5::uint4 MD5::G(uint4 x, uint4 y, uint4 z) {
  return (x&z) | (y&~z);
}
 
inline MD5::uint4 MD5::H(uint4 x, uint4 y, uint4 z) {
  return x^y^z;
}
 
inline MD5::uint4 MD5::I(uint4 x, uint4 y, uint4 z) {
  return y ^ (x | ~z);
}
 
// rotate_left rotates x left n bits.
inline MD5::uint4 MD5::rotate_left(uint4 x, int n) {
  return (x << n) | (x >> (32-n));
}
 
// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
// Rotation is separate from addition to prevent recomputation.
inline void MD5::FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
  a = rotate_left(a+ F(b,c,d) + x + ac, s) + b;
}
 
inline void MD5::GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
  a = rotate_left(a + G(b,c,d) + x + ac, s) + b;
}
 
inline void MD5::HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
  a = rotate_left(a + H(b,c,d) + x + ac, s) + b;
}
 
inline void MD5::II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
  a = rotate_left(a + I(b,c,d) + x + ac, s) + b;
}
 
//////////////////////////////////////////////
 
// default ctor, just initailize
MD5::MD5()
{
  init();
}
 
//////////////////////////////////////////////
 
// nifty shortcut ctor, compute MD5 for string and finalize it right away
MD5::MD5(const std::string &text)
{
  init();
  update(text.c_str(), text.length());
  finalize();
}
 
//////////////////////////////
 
void MD5::init()
{
  finalized=false;
 
  count[0] = 0;
  count[1] = 0;
 
  // load magic initialization constants.
  state[0] = 0x67452301;
  state[1] = 0xefcdab89;
  state[2] = 0x98badcfe;
  state[3] = 0x10325476;
}
 
//////////////////////////////
 
// decodes input (unsigned char) into output (uint4). Assumes len is a multiple of 4.
void MD5::decode(uint4 output[], const uint1 input[], size_type len)
{
  for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
    output[i] = ((uint4)input[j]) | (((uint4)input[j+1]) << 8) |
      (((uint4)input[j+2]) << 16) | (((uint4)input[j+3]) << 24);
}
 
//////////////////////////////
 
// encodes input (uint4) into output (unsigned char). Assumes len is
// a multiple of 4.
void MD5::encode(uint1 output[], const uint4 input[], size_type len)
{
  for (size_type i = 0, j = 0; j < len; i++, j += 4) {
    output[j] = input[i] & 0xff;
    output[j+1] = (input[i] >> 8) & 0xff;
    output[j+2] = (input[i] >> 16) & 0xff;
    output[j+3] = (input[i] >> 24) & 0xff;
  }
}
 
//////////////////////////////
 
// apply MD5 algo on a block
void MD5::transform(const uint1 block[blocksize])
{
  uint4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];
  decode (x, block, blocksize);
 
  /* Round 1 */
  FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
  FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
  FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
  FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
  FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
  FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
  FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
  FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
  FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
  FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
  FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
  FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
  FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
  FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
  FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
  FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */
 
  /* Round 2 */
  GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
  GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
  GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
  GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
  GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
  GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
  GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
  GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
  GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
  GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
  GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
  GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
  GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
  GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
  GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
  GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */
 
  /* Round 3 */
  HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
  HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
  HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
  HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
  HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
  HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
  HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
  HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
  HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
  HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
  HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
  HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
  HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
  HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
  HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
  HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */
 
  /* Round 4 */
  II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
  II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
  II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
  II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
  II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
  II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
  II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
  II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
  II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
  II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
  II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
  II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
  II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
  II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
  II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
  II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */
 
  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
 
  // Zeroize sensitive information.
  memset(x, 0, sizeof x);
}
 
//////////////////////////////
 
// MD5 block update operation. Continues an MD5 message-digest
// operation, processing another message block
void MD5::update(const unsigned char input[], size_type length)
{
  // compute number of bytes mod 64
  size_type index = count[0] / 8 % blocksize;
 
  // Update number of bits
  if ((count[0] += (length << 3)) < (length << 3))
    count[1]++;
  count[1] += (length >> 29);
 
  // number of bytes we need to fill in buffer
  size_type firstpart = 64 - index;
 
  size_type i;
 
  // transform as many times as possible.
  if (length >= firstpart)
  {
    // fill buffer first, transform
    memcpy(&buffer[index], input, firstpart);
    transform(buffer);
 
    // transform chunks of blocksize (64 bytes)
    for (i = firstpart; i + blocksize <= length; i += blocksize)
      transform(&input[i]);
 
    index = 0;
  }
  else
    i = 0;
 
  // buffer remaining input
  memcpy(&buffer[index], &input[i], length-i);
}
 
//////////////////////////////
 
// for convenience provide a verson with signed char
void MD5::update(const char input[], size_type length)
{
  update((const unsigned char*)input, length);
}
 
//////////////////////////////
 
// MD5 finalization. Ends an MD5 message-digest operation, writing the
// the message digest and zeroizing the context.
MD5& MD5::finalize()
{
  static unsigned char padding[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };
 
  if (!finalized) {
    // Save number of bits
    unsigned char bits[8];
    encode(bits, count, 8);
 
    // pad out to 56 mod 64.
    size_type index = count[0] / 8 % 64;
    size_type padLen = (index < 56) ? (56 - index) : (120 - index);
    update(padding, padLen);
 
    // Append length (before padding)
    update(bits, 8);
 
    // Store state in digest
    encode(digest, state, 16);
 
    // Zeroize sensitive information.
    memset(buffer, 0, sizeof buffer);
    memset(count, 0, sizeof count);
 
    finalized=true;
  }
 
  return *this;
}
 
//////////////////////////////
 
// return hex representation of digest as string
std::string MD5::hexdigest() const
{
  if (!finalized)
    return "";
 
  char* buf = new char[33];
  for (int i=0; i<16; i++)
    sprintf(buf+i*2, "%02x", digest[i]);
  buf[32]=0;
 
  std::string ret(buf);
  delete [] buf;
  buf = NULL;
  return ret;
}
 
//////////////////////////////
 
std::ostream& operator<<(std::ostream& out, MD5 md5)
{
  return out << md5.hexdigest();
}
 
//////////////////////////////
 
std::string md5(const std::string str)
{
    MD5* md5 = new MD5(str);
 
    string ret = md5->hexdigest();
    delete md5;
	return ret;
}

string QuotedPrintable_encode(const string &input)
{
    stringstream ss;

    char byte;
    const char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    for (unsigned int i = 0; i < input.size() ; ++i)
    {
        byte = input[i];

        if ((byte == 0x20) || ((byte >= 33) && (byte <= 126) && (byte != 61)))
        {
            ss << byte;
        }
        else
        {
            ss 
    		<< '='
			<< hex[((byte >> 4) & 0x0F)]
			<< hex[(byte & 0x0F)];
        }
    }

    return ss.str();
}


string QuotedPrintable_decode(const string &input)
{
    //                    0  1  2  3  4  5  6  7  8  9  :  ;  <  =  >  ?  @  A   B   C   D   E   F
    const int hexVal[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15};

    stringstream ss;

    for (unsigned int i = 0; i < input.size(); ++i)
    {
        if (input.at(i) == '=')
        {
            ss << (char)((hexVal[input.at(i+1) - '0'] << 4) + hexVal[input.at(i+2) - '0']);
            i+=2;
        }
        else
        {
            ss  << input.at(i);
        }
    }

    return ss.str();
}

inline std::string trim(const std::string &s, char k = '\0')
{
    if(s.empty()) return s;
	 if(k=='\0'){
		unsigned int start = 0;
		for(;start<s.size();++start){
			if(!std::isspace(s[start]))
				break;
		}
		unsigned int end = s.size()-1;
		for(;end > start; --end){
			if(!std::isspace(s[end]))
				break;
		}
		if(end < start)
			return "";
		return s.substr(start, end-start+1);
	}
	
	unsigned int start = 0;
	for(;start<s.size();++start){
		if(s[start] != k)
			break;
	}
	unsigned int end = s.size()-1;
	for(;end > start; --end){
		
        if(s[end] != k)
			break;
	}
	if(end < start)
		return "";
	return s.substr(start, end-start+1);
	
	
	
}

string urlencode(const string &value) {
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;

    for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
        string::value_type c = (*i);

        // Keep alphanumeric and other accepted characters intact
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << '%' << setw(2) << int((unsigned char) c);
    }

    return escaped.str();
}

string inject_html(const string &s, const string &base_url, const string &track_url) {
    stringstream ret;
	size_t offset = 0;
	while(true){
		size_t open = s.find("<", offset);
		if(open == string::npos)
			break;
			
		ret << s.substr(offset,open-offset);
		
		size_t close = s.find(">", open);
		if(close == string::npos)
			break;
			
		size_t start_tag = open+1;
		for(;start_tag<close;++start_tag){
			if(!isspace(s[start_tag]))
				break;
		}
		size_t end_tag = start_tag+1;
		
		for(;end_tag<close;++end_tag){
			if(isspace(s[end_tag]))
				break;
		}
		string tag = s.substr(start_tag, end_tag-start_tag);
		offset = close+1;
		/*if(tag.empty()) continue;
		if(tag[0] == '/'){ //closing tag
			continue;
		}*/
		if(tag.size() == 1 && (tag == "a" || tag == "A")){
			//cout<< open << " " << close << " " << tag <<endl;
			ret << "<a";
			//prendo attributi
			size_t offset_end_tag = end_tag;
			while(offset_end_tag < close){
				size_t start_attrib = offset_end_tag;
				for(;start_attrib<close;++start_attrib){
					if(!isspace(s[start_attrib]))
						break;
				}
                if(start_attrib == close)
                    break;
				size_t end_attrib = start_attrib+1;
				for(;end_attrib<close;++end_attrib){
					if(isspace(s[end_attrib]) || s[end_attrib] == '=')
						break;
				}
				string attrib = s.substr(start_attrib, end_attrib-start_attrib);
				std::transform(attrib.begin(), attrib.end(), attrib.begin(), ::tolower);
				//if(attrib == "href"){
					//cout << "\tAttribName: " << attrib << endl;
					size_t start_value = end_attrib+1;
					for(;start_value<close;++start_value){
						if(!isspace(s[start_value]) && s[start_value] != '=')
							break;
					}
					char must_end = s[start_value];
					//cout << "\t\t"<<must_end<<endl;
					size_t end_value = start_value+1;
					if(must_end != '"' && must_end != '\'')
						must_end = '\0';
					else ++start_value;
					for(;end_value<close;++end_value){
						if((must_end == '\0' && isspace(s[end_value])) || (must_end != '\0' && s[end_value] == must_end ) )
							break;
					}
					string attribValue = s.substr(start_value, end_value-start_value);
                    if(attribValue == ">")
                        attribValue = "";
					//cout << "\tAttribValue: " << attribValue << endl;
				
					offset_end_tag = end_value+1;
					if(attrib == "href"){
						attribValue = base_url + urlencode(attribValue);
					}
					ret << " " << attrib << "=" << must_end << attribValue << must_end;
				//}
			}
			
			ret << ">";
		} else {
			ret << s.substr(open, close-open+1);
			if(tag.size() == 4){
				std::transform(tag.begin(), tag.end(), tag.begin(), ::tolower);
				if(tag == "body"){
					ret<<"<img src=\""<< track_url << "\" alt=\"\" width=\"1\" height=\"1\" border=\"0\" style=\"display:block;\" />";
				}
			}
		}
		//ret << s.substr(open, close-open+1);
		
	}
	ret << s.substr(offset);
	return ret.str();
}


string CompressHtml(const string &input){
    stringstream ss;
	char byte;
	bool f;
	for (size_t i = 0; i < input.size() ;)
    {
		f = true;
		do{
			byte = input[++i-1];
			if(byte == '\r' || byte == '\n' || byte == '\t' || byte == ' '){
				if(f){
					ss << ' ';
			        f = false;
				}
			} else {
				ss << byte;
				break;
			}
		} while (true);
		
	}
	
	//cout << ss.str() << flush;
	//cout << "AAAAAAAAA" <<endl;
	//exit(1);
	return ss.str();
}
#include <mutex>
template <
    typename T,
    template<typename T, typename> class ContainerType,
    typename Alloc = std::allocator<T>
>
class GenericTS{
    ContainerType<T, Alloc> container;
    mutex _m;
    public:
    void push_back(T item){
        _m.lock();
        container.push_back(item);
        _m.unlock();
    }
    
    void print(){
        for(typename ContainerType<T, Alloc>::iterator it = container.begin(); it != container.end(); ++it){
            cout << *it << endl;
        }
    }
    
    T pop_front(){
        _m.lock();
        T item = container.front();
        container.pop_front();
        _m.unlock();
        return item;
    }
    
    size_t size(){
        _m.lock();
        size_t r = container.size();
        _m.unlock();
        return r;
    }
    
};

int main(){
    
    // usage:
    GenericTS<int, std::vector> test;
    test.push_back(10);
    test.push_back(20);
    test.push_back(22);
    test.pop_front();
    test.print();
    //cout << ":"<< CompressHtml("CIAO    asd\n\t  ciao") << endl;
    
    //string asd = inject_html("<a href=\"http://emprego-brasil.com/unsubscribe.php?email=pippoqr%40gmail.com\" style=\"text-decoration:none;color: #626262;\" d= >", "http://www.fff.com/", "asdasd");
    
    //cout <<  asd << endl;
    
    //string str = decode_html_entities("aaa&raquo;ciao &#39; prova &#338; aa");
    //cout<<str<<" "<<str.size() << " &#338;";
    //cout<<md5("dialysisjobsweekly.com-Patient Care Technician-Fresenius Medical Care. Madison-");
    
    //cout<<QuotedPrintable_encode("► Ciao come va? ! = èé£$%&/(");
    //cout<<QuotedPrintable_encode("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    
    //cout<<trim(" ")<<"b";
    return 0;
}
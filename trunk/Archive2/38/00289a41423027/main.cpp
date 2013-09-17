# Include <iostream> 
# include <lokalita>
 
int main ( ) 
{ 
    std :: wcout  <<  "užívateľom preferované locale nastavenie je"  << std :: locale ( "" ) . Meno ( ) . c_str ( )  <<  " \ n " ; 
    / / pri štarte, globálne locale je "C" locale 
    std :: wcout  <<  1.000,01  <<  ' \ n ' , 
    / / nahradiť C + + globálnej národnej, rovnako ako národné prostredie C s užívateľom preferované locale 
    std :: locale :: globálne ( std :: locale ( "" ) ) ; 
    / / používať nové globálne prostredie pre budúce široký znak výstupného 
    std :: wcout . vštiepiť komu čo ( std :: locale ( ) ) ; 
    / / výstup rovnaký počet opäť 
    std :: wcout  <<  1000,01  <<  " \ n " ; 
}
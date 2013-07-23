#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
srand(time(0));
int count;
int att11;
int att22;
int att33;
int att44;
int pokemon;
int total;
do 
{
int playerChoice1;
cout << "Welcome to the TRUE random Pokémon team generator" << endl;
cout << "Do you want to enable the Fakemon? Press 1 for yes and 2 for no" << endl;
cin >> playerChoice1;
playerChoice1 = 1;
if (playerChoice1 != 1 && playerChoice1 != 2) {
cout << "false input" << endl;
break;
}
cout << "The program wil now generate and print the 100% random pokemon team" << endl;
cout << "Copy everything under the next line" << endl;
cout << " " << endl;
total = 6;
while (total > 0)
{
if (playerChoice1 == 1)
{
pokemon = rand() %712;
}
else if (playerChoice1 == 2)
{
pokemon = rand() %696;
}
pokemon = pokemon + 1;
total = total - 1;
if (pokemon == 1) {
cout << "Bulbasaur @" ;
}
else if (pokemon == 2) {
cout << "Ivysaur @" ;
} 
else if(pokemon == 3) {
cout << "Venusaur @" ;
} 
else if (pokemon == 4) {
cout << "Charmander @" ;
} 
else if (pokemon == 5) {
cout << "Charmeleon @" ;
} 
else if (pokemon == 6) {
cout << "Charizard @" ;
} 
else if (pokemon == 7) {
cout << "Squirtle @" ;
} 
else if (pokemon == 8) {
cout << "Wartortle @" ;
} 
else if (pokemon == 9) {
cout << "Blastoise @" ;
} 
else if (pokemon == 10) {
cout << "Caterpie @" ;
} 
else if (pokemon == 11) {
cout << "Metapod @" ;
} 
else if (pokemon == 12) {
cout << "Butterfree @" ;
} 
else if (pokemon == 13) {
cout << "Weedle @" ;
} 
else if (pokemon == 14) {
cout << "Kakuna @" ;
} 
else if (pokemon == 15) {
cout << "Beedrill @" ;
} 
else if (pokemon == 16) {
cout << "Pidgey @" ;
} 
else if (pokemon == 17) {
cout << "Pidgeotto @" ;
} 
else if (pokemon == 18) {
cout << "Pidgeot @" ;
} 
else if (pokemon == 19) {
cout << "Rattata @" ;
} 
else if (pokemon == 20) {
cout << "Raticate @" ;
} 
else if (pokemon == 21) {
cout << "Spearow @" ;
} 
else if (pokemon == 22) {
cout << "Fearow @" ;
} 
else if (pokemon == 23) {
cout << "Ekans @" ;
} 
else if (pokemon == 24) {
cout << "Arbok @" ;
} 
else if (pokemon == 25) {
cout << "Pikachu @" ;
} 
else if (pokemon == 26) {
cout << "Raichu @" ;
} 
else if (pokemon == 27) {
cout << "Sandshrew @" ;
} 
else if (pokemon == 28) {
cout << "Sandslash @" ;
} 
else if (pokemon == 29) {
cout << "NidoranF (F) @" ;
} 
else if (pokemon == 30) {
cout << "Nidorina (F) @" ;
} 
else if (pokemon == 31) {
cout << "Nidoqueen (F) @" ;
} 
else if (pokemon == 32) {
cout << "NidoranM (M) @" ;
} 
else if (pokemon == 33) {
cout << "Nidorino (M) @" ;
} 
else if (pokemon == 34) {
cout << "Nidoking (M) @" ;
} 
else if (pokemon == 35) {
cout << "Clefairy @" ;
} 
else if (pokemon == 36) {
cout << "Clefable @" ;
} 
else if (pokemon == 37) {
cout << "Vulpix @" ;
} 
else if (pokemon == 38) {
cout << "Ninetales @" ;
} 
else if (pokemon == 39) {
cout << "Jigglypuff @" ;
} 
else if (pokemon == 40) {
cout << "Wigglytuff @" ;
} 
else if (pokemon == 41) {
cout << "Zubat @" ;
} 
else if (pokemon == 42) {
cout << "Golbat @" ;
} 
else if (pokemon == 43) {
cout << "Oddish @" ;
} 
else if (pokemon == 44) {
cout << "Gloom @" ;
} 
else if (pokemon == 45) {
cout << "Vileplume @" ;
} else if (pokemon == 46) {
cout << "Paras @" ;
} else if (pokemon == 47) {
cout << "Parasect @" ;
} else if (pokemon == 48) {
cout << "Venonat @" ;
} else if (pokemon == 49) {
cout << "Venomoth @" ;
} else if (pokemon == 50) {
cout << "Diglett @" ;
} else if (pokemon == 51) {
cout << "Dugtrio @" ;
} else if (pokemon == 52) {
cout << "Meowth @" ;
} else if (pokemon == 53) {
cout << "Persian @" ;
} else if (pokemon == 54) {
cout << "Psyduck @" ;
} else if (pokemon == 55) {
cout << "Golduck @" ;
} else if (pokemon == 56) {
cout << "Monkey (Mankey) @" ;
} else if (pokemon == 57) {
cout << "Primeape @" ;
} else if (pokemon == 58) {
cout << "Growlithe @" ;
} else if (pokemon == 59) {
cout << "Arcanine @" ;
} else if (pokemon == 60) {
cout << "Poliwag @" ;
} else if (pokemon == 61) {
cout << "Poliwhirl @" ;
} else if (pokemon == 62) {
cout << "Poliwrath @" ;
} else if (pokemon == 63) {
cout << "Abra @" ;
} else if (pokemon == 64) {
cout << "Kadabra @" ;
} else if (pokemon == 65) {
cout << "Alakazam @" ;
} else if (pokemon == 66) {
cout << "Machop @" ;
} else if (pokemon == 67) {
cout << "Machoke @" ;
} else if (pokemon == 68) {
cout << "Machamp @" ;
} else if (pokemon == 69) {
cout << "Bellsprout @" ;
} else if (pokemon == 70) {
cout << "Weepinbell @" ;
} else if (pokemon == 71) {
cout << "Victreebel @" ;
} else if (pokemon == 72) {
cout << "Tentacool @" ;
} else if (pokemon == 73) {
cout << "Tentacruel @" ;
} else if (pokemon == 74) {
cout << "Geodude @" ;
} else if (pokemon == 75) {
cout << "Graveler @" ;
} else if (pokemon == 76) {
cout << "Golem @" ;
} else if (pokemon == 77) {
cout << "Ponyta @" ;
} else if (pokemon == 78) {
cout << "Rapidash @" ;
} else if (pokemon == 79) {
cout << "Slowpoke @" ;
} else if (pokemon == 80) {
cout << "Slowbro @" ;
} else if (pokemon == 81) {
cout << "Magnemite @" ;
} else if (pokemon == 82) {
cout << "Magneton @" ;
} else if (pokemon == 83) {
cout << "Farfetch'd @" ;
} else if (pokemon == 84) {
cout << "Doduo @" ;
} else if (pokemon == 85) {
cout << "Dodrio @" ;
} else if (pokemon == 86) {
cout << "Seel @" ;
} else if (pokemon == 87) {
cout << "Dewgong @" ;
} else if (pokemon == 88) {
cout << "Grimer @" ;
} else if (pokemon == 89) {
cout << "Muk @" ;
} else if (pokemon == 90) {
cout << "Shellder @" ;
} else if (pokemon == 91) {
cout << "Cloyster @" ;
} else if (pokemon == 92) {
cout << "Gastly @" ;
} else if (pokemon == 93) {
cout << "Haunter @" ;
} else if (pokemon == 94) {
cout << "Gengar @" ;
} else if (pokemon == 95) {
cout << "Onix @" ;
} else if (pokemon == 96) {
cout << "Drowzee @" ;
} else if (pokemon == 97) {
cout << "Hypno @" ;
} else if (pokemon == 98) {
cout << "Krabby @" ;
} else if (pokemon == 99) {
cout << "Kingler @" ;
} else if (pokemon == 100) {
cout << "Voltorb @" ;
} else if (pokemon == 101) {
cout << "Electrode @" ;
} else if (pokemon == 102) {
cout <<"Exeggcute @" ;
} else if (pokemon == 103) {
cout << "Exeggutor @" ;
} else if (pokemon == 104) {
cout << "Cubone @" ;
} else if (pokemon == 105) {
cout << "Marowak @" ;
} else if (pokemon == 106) {
cout << "Hitmonlee (M) @" ;
} else if (pokemon == 107) {
cout << "Hitmonchan (M) @" ;
} else if (pokemon == 108) {
cout << "Lickitung @" ;
} else if (pokemon == 109) {
cout << "Koffing @" ;
} else if (pokemon == 110) {
cout << "Weezing @" ;
} else if (pokemon == 111) {
cout << "Rhyhorn @" ;
} else if (pokemon == 112) {
cout << "Rhydon @" ;
} else if (pokemon == 113) {
cout << "Chansey (F) @" ;
} else if (pokemon == 114) {
cout << "Tangela @" ;
} else if (pokemon == 115) {
cout << "Kangaskhan (F) @" ;
} else if (pokemon == 116) {
cout << "Horsea @" ;
} else if (pokemon == 117) {
cout << "Seadra @" ;
} else if (pokemon == 118) {
cout << "Goldeen @" ;
} else if (pokemon == 119) {
cout << "Seaking @" ;
} else if (pokemon == 120) {
cout << "Staryu @" ;
} else if (pokemon == 121) {
cout << "Starmie @" ;
} else if (pokemon == 122) {
cout << "Mr. Mime @" ;
} else if (pokemon == 123) {
cout << "Scyther @" ;
} else if (pokemon == 124) {
cout << "Jynx (F) @" ;
} else if (pokemon == 125) {
cout << "Electabuzz @" ;
} else if (pokemon == 126) {
cout << "Magmar @" ;
} else if (pokemon == 127) {
cout << "Pinsir @" ;
} else if (pokemon == 128) {
cout << "Tauros (M) @" ;
} else if (pokemon == 129) {
cout << "Magikarp @" ;
} else if (pokemon == 130) {
cout << "Gyarados @" ;
} else if (pokemon == 131) {
cout << "Lapras @" ;
} else if (pokemon == 132) {
cout << "Ditto @" ;
} else if (pokemon == 133) {
cout << "Eevee @" ;
} else if (pokemon == 134) {
cout << "Vaporeon @" ;
} else if (pokemon == 135) {
cout << "Jolteon @" ;
} else if (pokemon == 136) {
cout << "Flareon @" ;
} else if (pokemon == 137) {
cout << "Porygon @" ;
} else if (pokemon == 138) {
cout << "Omanyte @" ;
} else if (pokemon == 139) {
cout << "Omastar @" ;
} else if (pokemon == 140) {
cout << "Kabuto @" ;
} else if (pokemon == 141) {
cout << "Kabutops @" ;
} else if (pokemon == 142) {
cout << "Aerodactyl @" ;
} else if (pokemon == 143) {
cout << "Snorlax @" ;
} else if (pokemon == 144) {
cout << "Articuno @" ;
} else if (pokemon == 145) {
cout << "Zapdos @" ;
} else if (pokemon == 146) {
cout << "Moltres @" ;
} else if (pokemon == 147) {
cout << "Dratini @" ;
} else if (pokemon == 148) {
cout << "Dragonair @" ;
} else if (pokemon == 149) {
cout << "Dragonite @" ;
} else if (pokemon == 150) {
cout << "Mewtwo @" ;
} else if (pokemon == 151) {
cout << "Mew @" ;
} else if (pokemon == 152) {
cout << "Chikorita @" ;
} else if (pokemon == 153) {
cout << "Bayleef @" ;
} else if (pokemon == 154) {
cout << "Meganium @" ;
} else if (pokemon == 155) {
cout << "Cyndaquil @" ;
} else if (pokemon == 156) {
cout << "Quilava @" ;
} else if (pokemon == 157) {
cout << "Typhlosion @" ;
} else if (pokemon == 158) {
cout << "Totodile @" ;
} else if (pokemon == 159) {
cout << "Croconaw @" ;
} else if (pokemon == 160) {
cout << "Feraligatr @" ;
} else if (pokemon == 161) {
cout << "Sentret @" ;
} else if (pokemon == 162) {
cout << "Furret @" ;
} else if (pokemon == 163) {
cout << "Hoothoot @" ;
} else if (pokemon == 164) {
cout << "Noctowl @" ;
} else if (pokemon == 165) {
cout << "Ledyba @" ;
} else if (pokemon == 166) {
cout << "Ledian @" ;
} else if (pokemon == 167) {
cout << "Spinarak @" ;
} else if (pokemon == 168) {
cout << "Ariados @" ;
} else if (pokemon == 169) {
cout << "Crobat @" ;
} else if (pokemon == 170) {
cout << "Chinchou @" ;
} else if (pokemon == 171) {
cout << "Lanturn @" ;
} else if (pokemon == 172) {
cout << "Pichu @" ;
} else if (pokemon == 173) {
cout << "Cleffa @" ;
} else if (pokemon == 174) {
cout << "Igglybuff @" ;
} else if (pokemon == 175) {
cout << "Togepi @" ;
} else if (pokemon == 176) {
cout << "Togetic @" ;
} else if (pokemon == 177) {
cout << "Natu @" ;
} else if (pokemon == 178) {
cout << "Xatu @" ;
} else if (pokemon == 179) {
cout << "Mareep @" ;
} else if (pokemon == 180) {
cout << "Flaaffy @" ;
} else if (pokemon == 181) {
cout << "Ampharos @" ;
} else if (pokemon == 182) {
cout << "Bellossom @" ;
} else if (pokemon == 183) {
cout << "Marill @" ;
} else if (pokemon == 184) {
cout << "Azumarill @" ;
} else if (pokemon == 185) {
cout << "Sudowoodo @" ;
} else if (pokemon == 186) {
cout << "Politoed @" ;
} else if (pokemon == 187) {
cout << "Hoppip @" ;
} else if (pokemon == 188) {
cout << "Skiploom @" ;
} else if (pokemon == 189) {
cout << "Jumpluff @" ;
} else if (pokemon == 190) {
cout << "Aipom @" ;
} else if (pokemon == 191) {
cout << "Sunkern @" ;
} else if (pokemon == 192) {
cout << "Sunflora @" ;
} else if (pokemon == 193) {
cout << "Yanma @" ;
} else if (pokemon == 194) {
cout << "Wooper @" ;
} else if (pokemon == 195) {
cout << "Quagmire (Quagsire) @" ;
} else if (pokemon == 196) {
cout << "Espeon @" ;
} else if (pokemon == 197) {
cout << "Umbreon @" ;
} else if (pokemon == 198) {
cout << "Murkrow @" ;
} else if (pokemon == 199) {
cout << "Slowking @" ;
} else if (pokemon == 200) {
cout << "Misdreavus @" ;
} else if (pokemon == 201) {
cout << "Unown @" ;
} else if (pokemon == 202) {
cout << "Wobbuffet @" ;
} else if (pokemon == 203) {
cout << "Girafarig @" ;
} else if (pokemon == 204) {
cout << "Pineco @" ;
} else if (pokemon == 205) {
cout << "Forretrss @" ;
} else if (pokemon == 206) {
cout << "Dunsparce @" ;
} else if (pokemon == 207) {
cout << "Gligar @" ;
} else if (pokemon == 208) {
cout << "Steelix @" ;
} else if (pokemon == 209) {
cout << "Snubbull @" ;
} else if (pokemon == 210) {
cout << "Granbull @" ;
} else if (pokemon == 211) {
cout << "Qwilfish @" ;
} else if (pokemon == 212) {
cout << "Scizor @" ;
} else if (pokemon == 213) {
cout << "Shuckle @" ;
} else if (pokemon == 214) {
cout << "Heracross @" ;
} else if (pokemon == 215) {
cout << "Sneasel @" ;
} else if (pokemon == 216) {
cout << "Teddiursa @" ;
} else if (pokemon == 217) {
cout << "Ursaring @" ;
} else if (pokemon == 218) {
cout << "Slugma @" ;
} else if (pokemon == 219) {
cout << "Magcargo @" ;
} else if (pokemon == 220) {
cout << "Swinub @" ;
} else if (pokemon == 221) {
cout << "Piloswine @" ;
} else if (pokemon == 222) {
cout << "Corsola @" ;
} else if (pokemon == 223) {
cout << "Remoraid @" ;
} else if (pokemon == 224) {
cout << "Octillery @" ;
} else if (pokemon == 225) {
cout << "Delibird @" ;
} else if (pokemon == 226) {
cout << "Mantine @" ;
} else if (pokemon == 227) {
cout << "Skarmory @" ;
} else if (pokemon == 228) {
cout << "Houndour @" ;
} else if (pokemon == 229) {
cout << "Houndoom @" ;
} else if (pokemon == 230) {
cout << "Kingdra @" ;
} else if (pokemon == 231) {
cout << "Phanpy @" ;
} else if (pokemon == 232) {
cout << "Donphan @" ;
} else if (pokemon == 233) {
cout << "Porygon2 @" ;
} else if (pokemon == 234) {
cout << "Stantler @" ;
} else if (pokemon == 235) {
cout << "Smeargle @" ;
} else if (pokemon == 236) {
cout << "Tyrogue (M) @" ;
} else if (pokemon == 237) {
cout << "Hitmontop (M) @" ;
} else if (pokemon == 238) {
cout << "Smoochum (F) @" ;
} else if (pokemon == 239) {
cout << "Elekid @" ;
} else if (pokemon == 240) {
cout << "Magby @" ;
} else if (pokemon == 241) {
cout << "Miltank (F) @" ;
} else if (pokemon == 242) {
cout << "Blissey (F) @" ;
} else if (pokemon == 243) {
cout << "Raikou @" ;
} else if (pokemon == 244) {
cout << "Entei @" ;
} else if (pokemon == 245) {
cout << "Suicune @" ;
} else if (pokemon == 246) {
cout << "Larvitar @" ;
} else if (pokemon == 247) {
cout << "Pupitar @" ;
} else if (pokemon == 248) {
cout << "Tyranitar @" ;
} else if (pokemon == 249) {
cout << "Lugia @" ;
} else if (pokemon == 250) {
cout << "Ho-Oh @" ;
} else if (pokemon == 251) {
cout << "Celebi @" ;
} else if (pokemon == 252) {
cout << "Treecko @" ;
} else if (pokemon == 253) {
cout << "Grovyle @" ;
} else if (pokemon == 254) {
cout << "Sceptile @" ;
} else if (pokemon == 255) {
cout << "Torchic @" ;
} else if (pokemon == 256) {
cout << "Combusken @" ;
} else if (pokemon == 257) {
cout << "Blaziken @" ;
} else if (pokemon == 258) {
cout << "Mudkip @" ;
} else if (pokemon == 259) {
cout << "Marshtomp @" ;
} else if (pokemon == 260) {
cout << "Swampert @" ;
} else if (pokemon == 261) {
cout << "Poochyena @" ;
} else if (pokemon == 262) {
cout << "Mightyena @" ;
} else if (pokemon == 263) {
cout << "Zigzagoon @" ;
} else if (pokemon == 264) {
cout << "Linoone @" ;
} else if (pokemon == 265) {
cout << "Wurmple @" ;
} else if (pokemon == 266) {
cout << "Silcoon @" ;
} else if (pokemon == 267) {
cout << "Beautifly @" ;
} else if (pokemon == 268) {
cout << "Cascoon @" ;
} else if (pokemon == 269) {
cout << "Dustox @" ;
} else if (pokemon == 270) {
cout << "Lotad @" ;
} else if (pokemon == 271) {
cout << "Lombre @" ;
} else if (pokemon == 272) {
cout << "Ludicolo @" ;
} else if (pokemon == 273) {
cout << "Seedot @" ;
} else if (pokemon == 274) {
cout << "Nuzleaf @" ;
} else if (pokemon == 275) {
cout << "Shiftry @" ;
} else if (pokemon == 276) {
cout << "Taillow @" ;
} else if (pokemon == 277) {
cout << "Swellow @" ;
} else if (pokemon == 278) {
cout << "Wingull @" ;
} else if (pokemon == 279) {
cout << "Pelipper @" ;
} else if (pokemon == 280) {
cout << "Ralts @" ;
} else if (pokemon == 281) {
cout << "Kirlia @" ;
} else if (pokemon == 282) {
cout << "Gardevoir (F) @" ;
} else if (pokemon == 283) {
cout << "Surskit @" ;
} else if (pokemon == 284) {
cout << "Masquerain @" ;
} else if (pokemon == 285) {
cout << "Shroomish @" ;
} else if (pokemon == 286) {
cout << "Breloom @" ;
} else if (pokemon == 287) {
cout << "Slakoth @" ;
} else if (pokemon == 288) {
cout << "Vigoroth @" ;
} else if (pokemon == 289) {
cout << "Slaking @" ;
} else if (pokemon == 290) {
cout << "Nincada @" ;
} else if (pokemon == 291) {
cout << "Ninjask @" ;
} else if (pokemon == 292) {
cout << "Shedinja @" ;
} else if (pokemon == 293) {
cout << "Whismur @" ;
} else if (pokemon == 294) {
cout << "Loudred @" ;
} else if (pokemon == 295) {
cout << "Exploud @" ;
} else if (pokemon == 296) {
cout << "Makuhita @" ;
} else if (pokemon == 297) {
cout << "Hariyama @" ;
} else if (pokemon == 298) {
cout << "Azurill @" ;
} else if (pokemon == 299) {
cout << "Nosepass @" ;
} else if (pokemon == 300) {
cout << "Skitty @" ;
} else if (pokemon == 301) {
cout << "Delcatty @" ;
} else if (pokemon == 302) {
cout << "Sableye @" ;
} else if (pokemon == 303) {
cout << "Mawile @" ;
} else if (pokemon == 304) {
cout << "Aron @" ;
} else if (pokemon == 305) {
cout << "Lairon @" ;
} else if (pokemon == 306) {
cout << "Aggron @" ;
} else if (pokemon == 307) {
cout << "Meditite @" ;
} else if (pokemon == 308) {
cout << "Medicham @" ;
} else if (pokemon == 309) {
cout << "Electrike @" ;
} else if (pokemon == 310) {
cout << "Manectric @" ;
} else if (pokemon == 311) {
cout << "Plusle @" ;
} else if (pokemon == 312) {
cout << "Minum @" ;
} else if (pokemon == 313) {
cout << "Volbeat (M) @" ;
} else if (pokemon == 314) {
cout << "Illumise (F) @" ;
} else if (pokemon == 315) {
cout << "Roselia @" ;
} else if (pokemon == 316) {
cout << "Gulpin @" ;
} else if (pokemon == 317) {
cout << "Swalot @" ;
} else if (pokemon == 318) {
cout << "Carvanha @" ;
} else if (pokemon == 319) {
cout << "Pedo (Sharpedo) @" ;
} else if (pokemon == 320) {
cout << "Wailmer @" ;
} else if (pokemon == 321) {
cout << "Less dense than Oxygen! (Wailord) @" ;
} else if (pokemon == 322) {
cout << "Numel @" ;
} else if (pokemon == 323) {
cout << "Camerupt @" ;
} else if (pokemon == 324) {
cout << "Torkoal @" ;
} else if (pokemon == 325) {
cout << "Spoink @" ;
} else if (pokemon == 326) {
cout << "Grumpig @" ;
} else if (pokemon == 327) {
cout << "Spinda @" ;
} else if (pokemon == 328) {
cout << "Trapinch @" ;
} else if (pokemon == 329) {
cout << "Vibrava @" ;
} else if (pokemon == 330) {
cout << "Flygon @" ;
} else if (pokemon == 331) {
cout << "Cacnea @" ;
} else if (pokemon == 332) {
cout << "Cacturne @" ;
} else if (pokemon == 333) {
cout << "Swablu @" ;
} else if (pokemon == 334) {
cout << "Altaria @" ;
} else if (pokemon == 335) {
cout << "Zangoose @" ;
} else if (pokemon == 336) {
cout << "Seviper @" ;
} else if (pokemon == 337) {
cout << "Lunatone @" ;
} else if (pokemon == 338) {
cout << "Solrock @" ;
} else if (pokemon == 339) {
cout << "Barboach @" ;
} else if (pokemon == 340) {
cout << "Whiscash @" ;
} else if (pokemon == 341) {
cout << "Corphish @" ;
} else if (pokemon == 342) {
cout << "Crawdaunt @" ;
} else if (pokemon == 343) {
cout << "Baltoy @" ;
} else if (pokemon == 344) {
cout << "Claydol @" ;
} else if (pokemon == 345) {
cout << "Lileep @" ;
} else if (pokemon == 346) {
cout << "Cradily @" ;
} else if (pokemon == 347) {
cout << "Anorith @" ;
} else if (pokemon == 348) {
cout << "Armaldo @" ;
} else if (pokemon == 349) {
cout << "Feebas @" ;
} else if (pokemon == 350) {
cout << "Milotic @" ;
} else if (pokemon == 351) {
cout << "Castform @" ;
} else if (pokemon == 650) {
cout << "Pichu-Spiky-eared @" ;
} else if (pokemon == 651) {
cout << "Castform-Rainy @" ;
} else if (pokemon == 652) {
cout << "Castform-Sunny @" ;
} else if (pokemon == 653) {
cout << "Castform-Snowy @" ;
} else if (pokemon == 352) {
cout << "Kecleon @" ;
} else if (pokemon == 353) {
cout << "Shuppet @" ;
} else if (pokemon == 354) {
cout << "Banette @" ;
} else if (pokemon == 355) {
cout << "Duskull @" ;
} else if (pokemon == 356) {
cout << "Dusclops @" ;
} else if (pokemon == 357) {
cout << "Tropius @" ;
} else if (pokemon == 358) {
cout << "Chimecho @" ;
} else if (pokemon == 359) {
cout << "Absol @" ;
} else if (pokemon == 360) {
cout << "Wynaut @" ;
} else if (pokemon == 361) {
cout << "Snorunt @" ;
} else if (pokemon == 362) {
cout << "Glalie (M) @" ;
} else if (pokemon == 363) {
cout << "Spheal @" ;
} else if (pokemon == 364) {
cout << "Sealeo @" ;
} else if (pokemon == 365) {
cout << "Walrein @" ;
} else if (pokemon == 366) {
cout << "Clamperl @" ;
} else if (pokemon == 367) {
cout << "Huntail @" ;
} else if (pokemon == 368) {
cout << "Gorebyss @" ;
} else if (pokemon == 369) {
cout << "Relicanth @" ;
} else if (pokemon == 370) {
cout << "Luvdisc @" ;
} else if (pokemon == 371) {
cout << "Bagon @" ;
} else if (pokemon == 372) {
cout << "Shelgon @" ;
} else if (pokemon == 373) {
cout << "Salamence @" ;
} else if (pokemon == 374) {
cout << "Beldum @" ;
} else if (pokemon == 375) {
cout << "Metang @" ;
} else if (pokemon == 376) {
cout << "Metagross @" ;
} else if (pokemon == 377) {
cout << "Regirock @" ;
} else if (pokemon == 378) {
cout << "Regice @" ;
} else if (pokemon == 379) {
cout << "Registeel @" ;
} else if (pokemon == 380) {
cout << "Latias (F) @" ;
} else if (pokemon == 381) {
cout << "Latios (M) @" ;
} else if (pokemon == 382) {
cout << "Kyogre @" ;
} else if (pokemon == 383) {
cout << "Groudon @" ;
} else if (pokemon == 384) {
cout << "Rayquaza @" ;
} else if (pokemon == 385) {
cout << "Jirachi @" ;
} else if (pokemon == 386) {
cout << "Deoxys @" ;
} else if (pokemon == 654) {
cout << "Deoxys-Attack @" ;
} else if (pokemon == 655) {
cout << "Deoxys-Defence @" ;
} else if (pokemon == 656) {
cout << "Deoxys-Speed @" ;
} else if (pokemon == 387) {
cout << "Turtwig @" ;
} else if (pokemon == 388) {
cout << "Grotle @" ;
} else if (pokemon == 389) {
cout << "Torterra @" ;
} else if (pokemon == 390) {
cout << "Chimchar @" ;
} else if (pokemon == 391) {
cout << "Monferno @" ;
} else if (pokemon == 392) {
cout << "Infernape @" ;
} else if (pokemon == 393) {
cout << "Piplup @" ;
} else if (pokemon == 394) {
cout << "Prinplup @" ;
} else if (pokemon == 395) {
cout << "Empoleon @" ;
} else if (pokemon == 396) {
cout << "Starly @" ;
} else if (pokemon == 397) {
cout << "Staravia @" ;
} else if (pokemon == 398) {
cout << "Staraptor @" ;
} else if (pokemon == 399) {
cout << "Bidoof @" ;
} else if (pokemon == 400) {
cout << "Bibarel @" ;
} else if (pokemon == 401) {
cout << "Kricketot @" ;
} else if (pokemon == 402) {
cout << "Kricketune @" ;
} else if (pokemon == 403) {
cout << "Shinx @" ;
} else if (pokemon == 404) {
cout << "Luxio @" ;
} else if (pokemon == 405) {
cout << "Luxray @" ;
} else if (pokemon == 406) {
cout << "Budew @" ;
} else if (pokemon == 407) {
cout << "Roserade @" ;
} else if (pokemon == 408) {
cout << "Cranidos @" ;
} else if (pokemon == 409) {
cout << "Rampardos @" ;
} else if (pokemon == 410) {
cout << "Shieldon @" ;
} else if (pokemon == 411) {
cout << "Bastiodon @" ;
} else if (pokemon == 412) {
cout << "Burmy @" ;
} else if (pokemon == 413) {
cout << "Wormadan (F) @" ;
} else if (pokemon == 657) {
cout << "Wormadan-Sandy (F) @" ;
} else if (pokemon == 658) {
cout << "Wormadan-Trash (F) @" ;
} else if (pokemon == 414) {
cout << "Mothim (M) @" ;
} else if (pokemon == 415) {
cout << "Combee @" ;
} else if (pokemon == 416) {
cout << "Vespiquen (F) @" ;
} else if (pokemon == 417) {
cout << "Pachirisu @" ;
} else if (pokemon == 418) {
cout << "Buizel @" ;
} else if (pokemon == 419) {
cout << "Floatzel @" ;
} else if (pokemon == 420) {
cout << "Cherubi @" ;
} else if (pokemon == 421) {
cout << "Cherrim @" ;
} else if (pokemon == 659) {
cout << "Cherrim-Sunshine @" ;
} else if (pokemon == 422) {
cout << "Shellos @" ;
} else if (pokemon == 423) {
cout << "Gastrodon @" ;
} else if (pokemon == 424) {
cout << "Ambipom @" ;
} else if (pokemon == 425) {
cout << "Drifloon @" ;
} else if (pokemon == 426) {
cout << "Drifblim @" ;
} else if (pokemon == 427) {
cout << "Buneary @" ;
} else if (pokemon == 428) {
cout << "Lopunny (F) @" ;
} else if (pokemon == 429) {
cout << "Mismagius @" ;
} else if (pokemon == 430) {
cout << "Honchkrow @" ;
} else if (pokemon == 431) {
cout << "Glameow @" ;
} else if (pokemon == 432) {
cout << "Purugly @" ;
} else if (pokemon == 433) {
cout << "Chingling @" ;
} else if (pokemon == 434) {
cout << "Stunky @" ;
} else if (pokemon == 435) {
cout << "Skuntank @" ;
} else if (pokemon == 436) {
cout << "Bronzor @" ;
} else if (pokemon == 437) {
cout << "Bronzong @" ;
} else if (pokemon == 438) {
cout << "Bonsly @" ;
} else if (pokemon == 439) {
cout << "Mime Jr. @" ;
} else if (pokemon == 440) {
cout << "Happiny (F) @" ;
} else if (pokemon == 441) {
cout << "Chatot @" ;
} else if (pokemon == 442) {
cout << "Spiritomb @" ;
} else if (pokemon == 443) {
cout << "Gible @" ;
} else if (pokemon == 444) {
cout << "Gabite @" ;
} else if (pokemon == 445) {
cout << "Garchomp @" ;
} else if (pokemon == 446) {
cout << "Munchlax @" ;
} else if (pokemon == 447) {
cout << "Riolu @" ;
} else if (pokemon == 448) {
cout << "Lucario @" ;
} else if (pokemon == 449) {
cout << "Hippopotas @" ;
} else if (pokemon == 450) {
cout << "Hippowdon @" ;
} else if (pokemon == 451) {
cout << "Skorupi @" ;
} else if (pokemon == 452) {
cout << "Drapion @" ;
} else if (pokemon == 453) {
cout << "Croagunk @" ;
} else if (pokemon == 454) {
cout << "Toxicroak @" ;
} else if (pokemon == 455) {
cout << "Carnivine @" ;
} else if (pokemon == 456) {
cout << "Finneon @" ;
} else if (pokemon == 457) {
cout << "Lumineon @" ;
} else if (pokemon == 458) {
cout << "Mantyke @" ;
} else if (pokemon == 459) {
cout << "Snover @" ;
} else if (pokemon == 460) {
cout << "Abomasnow @" ;
} else if (pokemon == 461) {
cout << "Weavile @" ;
} else if (pokemon == 462) {
cout << "Magnezone @" ;
} else if (pokemon == 463) {
cout << "Lickilicky @" ;
} else if (pokemon == 464) {
cout << "Rhyperior @" ;
} else if (pokemon == 465) {
cout << "Tangrowth @" ;
} else if (pokemon == 466) {
cout << "Electivire @" ;
} else if (pokemon == 467) {
cout << "Magmortar @" ;
} else if (pokemon == 468) {
cout << "Togekiss @" ;
} else if (pokemon == 469) {
cout << "Yanmega @" ;
} else if (pokemon == 470) {
cout << "Leafeon @" ;
} else if (pokemon == 471) {
cout << "Glaceon @" ;
} else if (pokemon == 472) {
cout << "Gliscor @" ;
} else if (pokemon == 473) {
cout << "Mamoswine @" ;
} else if (pokemon == 474) {
cout << "Porygon-Z @" ;
} else if (pokemon == 475) {
cout << "Gallade (M) @" ;
} else if (pokemon == 476) {
cout << "Probopass @" ;
} else if (pokemon == 477) {
cout << "Dusknoir @" ;
} else if (pokemon == 478) {
cout << "Froslass (F) @" ;
} else if (pokemon == 479) {
cout << "Rotom @" ;
} else if (pokemon == 660) {
cout << "Rotom-Fan @" ;
} else if (pokemon == 661) {
cout << "Rotom-Frost @" ;
} else if (pokemon == 662) {
cout << "Rotom-Heat @" ;
} else if (pokemon == 663) {
cout << "Rotom-Mow @" ;
} else if (pokemon == 664) {
cout << "Rotom-Wash @" ;
} else if (pokemon == 480) {
cout << "Uxie @" ;
} else if (pokemon == 481) {
cout << "Mesprit @" ;
} else if (pokemon == 482) {
cout << "Azelf @" ;
} else if (pokemon == 483) {
cout << "Dialga @" ;
} else if (pokemon == 484) {
cout << "Palkia @" ;
} else if (pokemon == 485) {
cout << "Heatran @" ;
} else if (pokemon == 486) {
cout << "Regigigas @" ;
} else if (pokemon == 487) {
cout << "Giratina @" ;
} else if (pokemon == 665) {
cout << "Giratina-Origin @" ;
} else if (pokemon == 488) {
cout << "Cresselia (F) @" ;
} else if (pokemon == 489) {
cout << "Phione @" ;
} else if (pokemon == 490) {
cout << "Manaphy @" ;
} else if (pokemon == 491) {
cout << "Darkrai @" ;
} else if (pokemon == 492) {
cout << "Shaymin @" ;
} else if (pokemon == 666) {
cout << "Shaymin-Sky @" ;
} else if (pokemon == 493) {
cout << "Arceus @" ;
} else if (pokemon == 667) {
cout << "Arceus-??? @" ;
} else if (pokemon == 668) {
cout << "Arceus-Bug @" ;
} else if (pokemon == 669) {
cout << "Arceus-Dark @" ;
} else if (pokemon == 670) {
cout << "Arceus-Dragon @" ;
} else if (pokemon == 671) {
cout << "Arceus-Electric @" ;
} else if (pokemon == 672) {
cout << "Arceus-Fighting @" ;
} else if (pokemon == 673) {
cout << "Arceus-Fire @" ;
} else if (pokemon == 674) {
cout << "Arceus-Flying @" ;
} else if (pokemon == 675) {
cout << "Arceus-Ghost @" ;
} else if (pokemon == 676) {
cout << "Arceus-Grass @" ;
} else if (pokemon == 677) {
cout << "Arceus-Ground @" ;
} else if (pokemon == 678) {
cout << "Arceus-Ice @" ;
} else if (pokemon == 679) {
cout << "Arceus-Poison @" ;
} else if (pokemon == 680) {
cout << "Arceus-Psychic @" ;
} else if (pokemon == 681) {
cout << "Arceus-Rock @" ;
} else if (pokemon == 682) {
cout << "Arceus-Steel @" ;
} else if (pokemon == 683) {
cout << "Arceus-Water @" ;
} else if (pokemon == 494) {
cout << "Victini @" ;
} else if (pokemon == 495) {
cout << "Snivy @" ;
} else if (pokemon == 496) {
cout << "Servine @" ;
} else if (pokemon == 497) {
cout << "Serperior @" ;
} else if (pokemon == 498) {
cout << "Tepig @" ;
} else if (pokemon == 499) {
cout << "Pignite @" ;
} else if (pokemon == 500) {
cout << "Emboar @" ;
} else if (pokemon == 501) {
cout << "Oshawott @" ;
} else if (pokemon == 502) {
cout << "Dewott @" ;
} else if (pokemon == 503) {
cout << "Samurott @" ;
} else if (pokemon == 504) {
cout << "Patrat @" ;
} else if (pokemon == 505) {
cout << "Watchog @" ;
} else if (pokemon == 506) {
cout << "Lillipup @" ;
} else if (pokemon == 507) {
cout << "Herdier @" ;
} else if (pokemon == 508) {
cout << "Stoutland @" ;
} else if (pokemon == 509) {
cout << "Purrloin @" ;
} else if (pokemon == 510) {
cout << "Leipard @" ;
} else if (pokemon == 511) {
cout << "Pansage @" ;
} else if (pokemon == 512) {
cout << "Simisage @" ;
} else if (pokemon == 513) {
cout << "Pansear @" ;
} else if (pokemon == 514) {
cout << "Simisear @" ;
} else if (pokemon == 515) {
cout << "Panpour @" ;
} else if (pokemon == 516) {
cout << "Simipour @" ;
} else if (pokemon == 517) {
cout << "Munna @" ;
} else if (pokemon == 518) {
cout << "Musharna @" ;
} else if (pokemon == 519) {
cout << "Pidove @" ;
} else if (pokemon == 520) {
cout << "Tranquill @" ;
} else if (pokemon == 521) {
cout << "Unfezant @" ;
} else if (pokemon == 522) {
cout << "Blitzle @" ;
} else if (pokemon == 523) {
cout << "Zebstrika @" ;
} else if (pokemon == 524) {
cout << "Roggenrola @" ;
} else if (pokemon == 525) {
cout << "Boldore @" ;
} else if (pokemon == 526) {
cout << "Gigalith @" ;
} else if (pokemon == 527) {
cout << "Woobat @" ;
} else if (pokemon == 528) {
cout << "Swoobat @" ;
} else if (pokemon == 529) {
cout << "Drilbur @" ;
} else if (pokemon == 530) {
cout << "Excadrill @" ;
} else if (pokemon == 531) {
cout << "Aurdino @" ;
} else if (pokemon == 532) {
cout << "Timburr @" ;
} else if (pokemon == 533) {
cout << "Herpderp (Gurdurr) @" ;
} else if (pokemon == 534) {
cout << "Conkledurr @" ;
} else if (pokemon == 535) {
cout << "Tympole @" ;
} else if (pokemon == 536) {
cout << "Palpitoad @" ;
} else if (pokemon == 537) {
cout << "Seismitoad @" ;
} else if (pokemon == 538) {
cout << "Throh (M) @" ;
} else if (pokemon == 539) {
cout << "Sawk (M) @" ;
} else if (pokemon == 540) {
cout << "Sewaddle @" ;
} else if (pokemon == 541) {
cout << "Swadloon @" ;
} else if (pokemon == 542) {
cout << "Leavanny @" ;
} else if (pokemon == 543) {
cout << "Venipede @" ;
} else if (pokemon == 544) {
cout << "Whirlipede @" ;
} else if (pokemon == 545) {
cout << "Scolipede @" ;
} else if (pokemon == 546) {
cout << "Cottonee @" ;
} else if (pokemon == 547) {
cout << "Whimsicott @" ;
} else if (pokemon == 548) {
cout << "Petilil (F) @" ;
} else if (pokemon == 549) {
cout << "Lilligant (F) @" ;
} else if (pokemon == 550) {
cout << "Basculin @" ;
} else if (pokemon == 684) {
cout << "Basculin-Blue-Striped @" ;
} else if (pokemon == 551) {
cout << "Sandile @" ;
} else if (pokemon == 552) {
cout << "Krokorok @" ;
} else if (pokemon == 553) {
cout << "Krookodile @" ;
} else if (pokemon == 554) {
cout << "Darumaka @" ;
} else if (pokemon == 555) {
cout << "Darmanitan @" ;
} else if (pokemon == 685) {
cout << "Darmanitan-Zen @" ;
} else if (pokemon == 556) {
cout << "Maractus @" ;
} else if (pokemon == 557) {
cout << "Dwebble @" ;
} else if (pokemon == 558) {
cout << "Crustle @" ;
} else if (pokemon == 559) {
cout << "Scraggy @" ;
} else if (pokemon == 560) {
cout << "Scrafty @" ;
} else if (pokemon == 561) {
cout << "Sigilyph @" ;
} else if (pokemon == 562) {
cout << "Yamask @" ;
} else if (pokemon == 563) {
cout << "Cofagrigus @" ;
} else if (pokemon == 564) {
cout << "Tirtouga @" ;
} else if (pokemon == 565) {
cout << "Carracosta @" ;
} else if (pokemon == 566) {
cout << "Archen @" ;
} else if (pokemon == 567) {
cout << "Archeops @" ;
} else if (pokemon == 568) {
cout << "Trubbish @" ;
} else if (pokemon == 569) {
cout << "Garbodor @" ;
} else if (pokemon == 570) {
cout << "Zorua @" ;
} else if (pokemon == 571) {
cout << "Zoroark @" ;
} else if (pokemon == 572) {
cout << "Minccino @" ;
} else if (pokemon == 573) {
cout << "Cinccino @" ;
} else if (pokemon == 574) {
cout << "Gothita @" ;
} else if (pokemon == 575) {
cout << "Gothorita @" ;
} else if (pokemon == 576) {
cout << "Gothitelle @" ;
} else if (pokemon == 577) {
cout << "Solosis @" ;
} else if (pokemon == 578) {
cout << "Duosion @" ;
} else if (pokemon == 579) {
cout << "Reuniclus @" ;
} else if (pokemon == 580) {
cout << "Ducklett @" ;
} else if (pokemon == 581) {
cout << "Swanna @" ;
} else if (pokemon == 582) {
cout << "Vanillite @" ;
} else if (pokemon == 583) {
cout << "Vanillish @" ;
} else if (pokemon == 584) {
cout << "Vanilluxe @" ;
} else if (pokemon == 585) {
cout << "Deerling @" ;
} else if (pokemon == 586) {
cout << "Sawsbuck @" ;
} else if (pokemon == 587) {
cout << "Emolga @" ;
} else if (pokemon == 588) {
cout << "Karrablast @" ;
} else if (pokemon == 589) {
cout << "Escavalier @" ;
} else if (pokemon == 590) {
cout << "Foongus @" ;
} else if (pokemon == 591) {
cout << "Amoonguss @" ;
} else if (pokemon == 592) {
cout << "Frillish @" ;
} else if (pokemon == 593) {
cout << "Jellicent @" ;
} else if (pokemon == 594) {
cout << "Alomomola @" ;
} else if (pokemon == 595) {
cout << "Joltik @" ;
} else if (pokemon == 596) {
cout << "Galvantula @" ;
} else if (pokemon == 597) {
cout << "Ferroseed @" ;
} else if (pokemon == 598) {
cout << "Ferrothorn @" ;
} else if (pokemon == 599) {
cout << "Klink @" ;
} else if (pokemon == 600) {
cout << "Klang @" ;
} else if (pokemon == 601) {
cout << "Klinklang @" ;
} else if (pokemon == 602) {
cout << "Tynamo @" ;
} else if (pokemon == 603) {
cout << "Eelektrik @" ;
} else if (pokemon == 604) {
cout << "Eelektross @" ;
} else if (pokemon == 605) {
cout << "Elgyem @" ;
} else if (pokemon == 606) {
cout << "Beheeyem @" ;
} else if (pokemon == 607) {
cout << "Litwick @" ;
} else if (pokemon == 608) {
cout << "Lampent @" ;
} else if (pokemon == 609) {
cout << "Chandelure @" ;
} else if (pokemon == 610) {
cout << "Axew @" ;
} else if (pokemon == 611) {
cout << "Fraxure @" ;
} else if (pokemon == 612) {
cout << "Haxorus @" ;
} else if (pokemon == 613) {
cout << "Cubchoo @" ;
} else if (pokemon == 614) {
cout << "Beartic @" ;
} else if (pokemon == 615) {
cout << "Cryogonal @" ;
} else if (pokemon == 616) {
cout << "Shelmet @" ;
} else if (pokemon == 617) {
cout << "Accelgor @" ;
} else if (pokemon == 618) {
cout << "Stunfisk @" ;
} else if (pokemon == 619) {
cout << "Mienfoo @" ;
} else if (pokemon == 620) {
cout << "Mienshao @" ;
} else if (pokemon == 621) {
cout << "Druddigon @" ;
} else if (pokemon == 622) {
cout << "Golett @" ;
} else if (pokemon == 623) {
cout << "Golurk @" ;
} else if (pokemon == 624) {
cout << "Pawniard @" ;
} else if (pokemon == 625) {
cout << "Bisharp @" ;
} else if (pokemon == 626) {
cout << "Bouffalant @" ;
} else if (pokemon == 627) {
cout << "Rufflet (M) @" ;
} else if (pokemon == 628) {
cout << "Braviary (M) @" ;
} else if (pokemon == 629) {
cout << "Vullaby (F) @" ;
} else if (pokemon == 630) {
cout << "Mandibuzz (F) @" ;
} else if (pokemon == 631) {
cout << "Heatmor @" ;
} else if (pokemon == 632) {
cout << "Durant @" ;
} else if (pokemon == 633) {
cout << "Deino @" ;
} else if (pokemon == 634) {
cout << "Zweilous @" ;
} else if (pokemon == 635) {
cout << "Hydreigon @" ;
} else if (pokemon == 636) {
cout << "Larvesta @" ;
} else if (pokemon == 637) {
cout << "Volcarona @" ;
} else if (pokemon == 638) {
cout << "Cobalion @" ;
} else if (pokemon == 639) {
cout << "Terrakion @" ;
} else if (pokemon == 640) {
cout << "Virizion @" ;
} else if (pokemon == 641) {
cout << "Tornadus (M) @" ;
} else if (pokemon == 686) {
cout << "Tornadus-Therian (M) @" ;
} else if (pokemon == 642) {
cout << "Thundurus (M) @" ;
} else if (pokemon == 687) {
cout << "Thundurus-Therian (M) @" ;
} else if (pokemon == 643) {
cout << "Reshiram @" ;
} else if (pokemon == 644) {
cout << "Zekrom @" ;
} else if (pokemon == 645) {
cout << "Landorus @" ;
} else if (pokemon == 688) {
cout << "Landorus-Therian @" ;
} else if (pokemon == 646) {
cout << "Kyurem @" ;
} else if (pokemon == 689) {
cout << "Kyurem-Black @" ;
} else if (pokemon == 690) {
cout << "Kyurem-White @" ;
} else if (pokemon == 647) {
cout << "Keldeo @" ;
} else if (pokemon == 691) {
cout << "Keldeo-Resolute @" ;
} else if (pokemon == 648) {
cout << "Meloetta @" ;
} else if (pokemon == 692) {
cout << "Meloetta-Pirouette @" ;
} else if (pokemon == 649) {
cout << "Genesect @" ;
} else if (pokemon == 693) {
cout << "Genesect-Burn @" ;
} else if (pokemon == 694) {
cout << "Genesect-Chill @" ;
} else if (pokemon == 695) {
cout << "Genesect-Douse @" ;
} 
else if (pokemon == 696) {
cout << "Genesect-Shock @" ;
} 
else if (pokemon == 697) {
cout << "Tomohawk @" ;
} 
else if (pokemon == 698) {
cout << "Necturna @" ;
} 
else if (pokemon == 699) {
cout << "Mollux @" ;
} 
else if (pokemon == 700) {
cout << "Aurumoth @" ;
} 
else if (pokemon == 701) {
cout << "Malaconda @" ;
} 
else if (pokemon == 702) {
cout << "Syclant @" ;
} 
else if (pokemon == 703) {
cout << "Revenankh @" ;
} 
else if (pokemon == 704) {
cout << "Pyroak @" ;
} 
else if (pokemon == 705) {
cout << "Fidgit @" ;
} 
else if (pokemon == 706) {
cout << "Stratagem @" ;
} 
else if (pokemon == 707) {
cout << "Arghonaut @" ;
} 
else if (pokemon == 708) {
cout << "Kitsunoh @" ;
} 
else if (pokemon == 709) {
cout << "Cyclohm @" ;
} 
else if (pokemon == 710) {
cout << "Colossoil @" ;
} 
else if (pokemon == 711) {
cout << "Krilowatt @" ;
} 
else if (pokemon == 712) {
cout << "Voodoom @" ;
}
int item;
item = rand() %225;
item = item + 1;
if (item == 1) {
cout << " Absorb Bulb" << endl;
    }
    else if (item == 2) 
    {
cout << " Adamant Orb" << endl;
    } 
    else if (item == 3) 
	{
cout << " Aguav Berry" << endl;
    } 
	else if (item == 4) 
	{
cout << " Air Balloon" << endl;
    } 
	else if (item == 5) 
	{
cout << " Apicot Berry" << endl;
    } 
	else if (item == 6) 
	{
cout << " Armor Fossil" << endl;
    } 
	else if (item == 7) 
	{
cout << " Aspear Berry" << endl;
    } 
	else if (item == 8) 
	{
cout << " Babiri Berry" << endl;
    } 
	else if (item == 9) 
	{
cout << " Belue Berry" << endl;
	} 
else if (item == 10) 
	{
cout << " Berry Juice" << endl;
    } 
else if (item == 11) 
	{
cout << " Big Root" << endl;
	} 
else if (item == 12) 
	{
cout << " Binding Band" << endl;
	} 
else if (item == 13) 
	{
cout << " Black Belt" << endl;
	} 
else if (item == 14) 
	{
cout << " Black Sludge" << endl;
} 
else if (item == 15) {
cout << " BlackGlasses" << endl;
} 
else if (item == 16) {
cout << " Bluk Berry" << endl;
} 
else if (item == 17) {
cout << " BrightPowder" << endl;
} 
else if (item == 18) {
cout << " Bug Gem" << endl; } 
else if (item == 19) {
cout << " Burn Drive" << endl; } 
else if (item == 20) {
cout << " Cell Battery" << endl; } 
else if (item == 21) {
cout << " Charcoal" << endl; } 
else if (item == 22) {
cout << " Charti Berry" << endl; } 
else if (item == 23) {
cout << " Cheri Berry" << endl; } 
else if (item == 24) {
cout << " Cherish Ball" << endl; } 
else if (item == 25) {
cout << " Chesto Berry" << endl; } 
else if (item == 26) {
cout << " Chilan Berry" << endl; } 
else if (item == 27) {
cout << " Chill Drive" << endl; } 
else if (item == 28) {
cout << " Choice Band" << endl; } 
else if (item == 29) {
cout << " Choice Scarf" << endl; } 
else if (item == 30) {
cout << " Choice Specs" << endl; } 
else if (item == 31) {
cout << " Chople Berry" << endl; } 
else if (item == 32) {
cout << " Claw Fossil" << endl; } 
else if (item == 33) {
cout << " Coba Berry" << endl; } 
else if (item == 34) {
cout << " Colbur Berry" << endl; } 
else if (item == 35) {
cout << " Cornn Berry" << endl; } 
else if (item == 36) {
cout << " Cover Fossil" << endl; } 
else if (item == 37) {
cout << " Custap Berry" << endl; } 
else if (item == 38) {
cout << " Damp Rock" << endl; } 
else if (item == 39) {
cout << " Dark Gem" << endl; } 
else if (item == 40) {
cout << " DeepSeaScale" << endl; } 
else if (item == 41) {
cout << " DeepSeaTooth" << endl; } 
else if (item == 42) {
cout << " Destiny Knot" << endl; } 
else if (item == 43) {
cout << " Dive Ball" << endl; } 
else if (item == 44) {
cout << " Dome Fossil" << endl; } 
else if (item == 45) {
cout << " Douse Drive" << endl; } 
else if (item == 46) {
cout << " Draco Plate" << endl; } 
else if (item == 47) {
cout << " Dragon Fang" << endl; } 
else if (item == 48) {
cout << " Dragon Gem" << endl; } 
else if (item == 49) {
cout << " Dread Plate" << endl; } 
else if (item == 50) {
cout << " Dream Ball" << endl; } 
else if (item == 51) {
cout << " Durin Berry" << endl; } 
else if (item == 52) {
cout << " Dusk Ball" << endl; } 
else if (item == 53) {
cout << " Earth Plate" << endl; } 
else if (item == 54) {
cout << " Eject Button" << endl; } 
else if (item == 55) {
cout << " Electirizer" << endl; } 
else if (item == 56) {
cout << " Electric Gem" << endl; } 
else if (item == 57) {
cout << " EnergyPowder" << endl; } 
else if (item == 58) {
cout << " Enigma Berry" << endl; } 
else if (item == 59) {
cout << " Eviolite" << endl; } 
else if (item == 60) {
cout << " Expert Belt" << endl; } 
else if (item == 61) {
cout << " Fast Ball" << endl; } 
else if (item == 62) {
cout << " Fighting Gem" << endl; } 
else if (item == 63) {
cout << " Figy Berry" << endl; } 
else if (item == 64) {
cout << " Fire Gem" << endl; } 
else if (item == 65) {
cout << " Fist Plate" << endl; } 
else if (item == 66) {
cout << " Flame Orb" << endl; } 
else if (item == 67) {
cout << " Flame Plate" << endl; } 
else if (item == 68) {
cout << " Float Stone" << endl; } 
else if (item == 69) {
cout << " Flying Gem" << endl; } 
else if (item == 70) {
cout << " Focus Band" << endl; } 
else if (item == 71) {
cout << " Focus Sash" << endl; } 
else if (item == 72) {
cout << " Full Incense" << endl; } 
else if (item == 73) {
cout << " Ganlon Berry" << endl; } 
else if (item == 74) {
cout << " Ghost Gem" << endl; } 
else if (item == 75) {
cout << " Grass Gem" << endl; } 
else if (item == 76) {
cout << " Great Ball" << endl; } 
else if (item == 77) {
cout << " Grepa Berry" << endl; } 
else if (item == 78) {
cout << " Grip Claw" << endl; } 
else if (item == 79) {
cout << " Griseous Orb" << endl; } 
else if (item == 80) {
cout << " Ground Gem" << endl; } 
else if (item == 81) {
cout << " Haban Berry" << endl; } 
else if (item == 82) {
cout << " Hard Stone" << endl; } 
else if (item == 83) {
cout << " Heal Ball" << endl; } 
else if (item == 84) {
cout << " Heat Rock" << endl; } 
else if (item == 85) {
cout << " Heavy Ball" << endl; } 
else if (item == 86) {
cout << " Helix Fossil" << endl; } 
else if (item == 87) {
cout << " Hondew Berry" << endl; } 
else if (item == 88) {
cout << " Iapapa Berry" << endl; } 
else if (item == 89) {
cout << " Ice Gem" << endl; } 
else if (item == 90) {
cout << " Icicle Plate" << endl; } 
else if (item == 91) {
cout << " Icy Rock" << endl; } 
else if (item == 92) {
cout << " Insect Plate" << endl; } 
else if (item == 93) {
cout << " Iron Ball" << endl; } 
else if (item == 94) {
cout << " Iron Ball" << endl; } 
else if (item == 95) {
cout << " Jaboca Berry" << endl; } 
else if (item == 96) {
cout << " Kasib Berry" << endl; } 
else if (item == 97) {
cout << " Kebia Berry" << endl; } 
else if (item == 98) {
cout << " Kelpsy Berry" << endl; } 
else if (item == 99) {
cout << " King's Rock" << endl; } 
else if (item == 100) {
cout << " Lagging Tail" << endl; } 
else if (item == 101) {
cout << " Lansat Berry" << endl; } 
else if (item == 102) {
cout << " Lax Incense" << endl; }
else if (item == 103) {
cout << " Leftovers" << endl; }
else if (item == 104) {
cout << " Leppa Berry" << endl; } 
else if (item == 105) {
cout << " Level Ball" << endl; }
else if (item == 106) {
cout << " Liechi Berry" << endl; } 
else if (item == 107) {
cout << " Life Orb" << endl; } 
else if (item == 108) {
cout << " Licht Ball" << endl; } 
else if (item == 109) {
cout << " Light Clay" << endl; }
else if (item == 110) {
cout << " Love Ball" << endl; } 
else if (item == 111) {
cout << " Lucky Punch" << endl; }
else if (item == 112) {
cout << " Lum Berry" << endl; }
else if (item == 113) {
cout << " Lure Ball" << endl; } 
else if (item == 114) {
cout << " Lustrous Orb" << endl; } 
else if (item == 115) {
cout << " Luxury Ball" << endl; } 
else if (item == 116) {
cout << " Macho Brace" << endl; } 
else if (item == 117) {
cout << " Magnet" << endl; } 
else if (item == 118) {
cout << " Mago Berry" << endl; } 
else if (item == 119) {
cout << " Magost Berry" << endl; } 
else if (item == 120) {
cout << " Mail" << endl; } 
else if (item == 121) {
cout << " Master Ball" << endl; } 
else if (item == 122) {
cout << " Meadow Plate" << endl; } 
else if (item == 123) {
cout << " Mental Herb" << endl; } 
else if (item == 124) {
cout << " Metal Coat" << endl; } 
else if (item == 125) {
cout << " Metal Powder" << endl; } 
else if (item == 126) {
cout << " Metronome" << endl; } 
else if (item == 127) {
cout << " Micle Berry" << endl; } 
else if (item == 128) {
cout << " Mind Plate" << endl; } 
else if (item == 129) {
cout << " Miracle Seed" << endl; } 
else if (item == 130) {
cout << " Moon Ball" << endl; } 
else if (item == 131) {
cout << " Muscle Band" << endl; } 
else if (item == 132) {
cout << " Mystic Water" << endl; } 
else if (item == 133) {
cout << " Nanab Berry" << endl; } 
else if (item == 134) {
cout << " Nest Ball" << endl; } 
else if (item == 135) {
cout << " Net Ball" << endl; } 
else if (item == 136) {
cout << " NeverMeltIce" << endl; } 
else if (item == 137) {
cout << " Nomel Berry" << endl; } 
else if (item == 138) {
cout << " Normal Gem" << endl; } 
else if (item == 139) {
cout << " Occa Berry" << endl; } 
else if (item == 140) {
cout << " Odd Incense" << endl; } 
else if (item == 141) {
cout << " Old Amber" << endl; } 
else if (item == 142) {
cout << " Oran Berry" << endl; } 
else if (item == 143) {
cout << " Pamtre Berry" << endl; } 
else if (item == 144) {
cout << " Park Ball" << endl; } 
else if (item == 145) {
cout << " Passho Berry" << endl; } 
else if (item == 146) {
cout << " Payapa Berry" << endl; } 
else if (item == 147) {
cout << " Pecha Berry" << endl; } 
else if (item == 148) {
cout << " Persim Berry" << endl; } 
else if (item == 149) {
cout << " Petaya Berry" << endl; } 
else if (item == 150) {
cout << " Pinap Berry" << endl; } 
else if (item == 151) {
cout << " Plume Fossil" << endl; } 
else if (item == 152) {
cout << " Poison Barb" << endl; } 
else if (item == 153) {
cout << " Poison Gem" << endl; } 
else if (item == 154) {
cout << " Poke Ball" << endl; } 
else if (item == 155) {
cout << " Pomeg Berry" << endl; } 
else if (item == 156) {
cout << " Power Herb" << endl; } 
else if (item == 157) {
cout << " Premier Ball" << endl; } 
else if (item == 158) {
cout << " Psychic Gem" << endl; } 
else if (item == 159) {
cout << " Qualot Berry" << endl; } 
else if (item == 160) {
cout << " Quick Ball" << endl; } 
else if (item == 161) {
cout << " Quick Claw" << endl; } 
else if (item == 162) {
cout << " Quick Powder" << endl; } 
else if (item == 163) {
cout << " Rabuta Berry" << endl; } 
else if (item == 164) {
cout << " Rare Bone" << endl; } 
else if (item == 165) {
cout << " Rawst Berry" << endl; } 
else if (item == 166) {
cout << " Razor Claw" << endl; } 
else if (item == 167) {
cout << " Razor Fang" << endl; } 
else if (item == 168) {
cout << " Razz Berry" << endl; } 
else if (item == 169) {
cout << " Red Card" << endl; } 
else if (item == 170) {
cout << " Repeat Ball" << endl; } 
else if (item == 171) {
cout << " Rindo Berry" << endl; } 
else if (item == 172) {
cout << " Ring Target" << endl; } 
else if (item == 173) {
cout << " Rock Gem" << endl; } 
else if (item == 174) {
cout << " Rock Incense" << endl; } 
else if (item == 175) {
cout << " Rocky Helmet" << endl; } 
else if (item == 176) {
cout << " Root Fossil" << endl; } 
else if (item == 177) {
cout << " Rose Incense" << endl; } 
else if (item == 178) {
cout << " Rowap Berry" << endl; } 
else if (item == 179) {
cout << " Safari Ball" << endl; } 
else if (item == 180) {
cout << " Salac Berry" << endl; } 
else if (item == 181) {
cout << " Scope Lens" << endl; } 
else if (item == 182) {
cout << " Sea Incense" << endl; } 
else if (item == 183) {
cout << " Sharp Beak" << endl; } 
else if (item == 184) {
cout << " Shed Shell" << endl; } 
else if (item == 185) {
cout << " Shell Bell" << endl; } 
else if (item == 186) {
cout << " Shock Drive" << endl; } 
else if (item == 187) {
cout << " Shuca Berry" << endl; } 
else if (item == 188) {
cout << " Silk Scarf" << endl; } 
else if (item == 189) {
cout << " SilverPowder" << endl; } 
else if (item == 190) {
cout << " Sitrus Berry" << endl; } 
else if (item == 191) {
cout << " Skull Fossil" << endl; } 
else if (item == 192) {
cout << " Sky Plate" << endl; } 
else if (item == 193) {
cout << " Smooth Rock" << endl; } 
else if (item == 194) {
cout << " Soft Sand" << endl; } 
else if (item == 195) {
cout << " Soul Dew" << endl; } 
else if (item == 196) {
cout << " Spell Tag" << endl; } 
else if (item == 197) {
cout << " Spelon Berry" << endl; } 
else if (item == 198) {
cout << " Splash Plate" << endl; } 
else if (item == 199) {
cout << " Spooky Plate" << endl; } 
else if (item == 200) {
cout << " Sport Ball" << endl; }
else if (item == 201) {
cout << " Starf Berry" << endl; } 
else if (item == 202) {
cout << " Steel Gem" << endl; } 
else if (item == 203) {
cout << " Stick" << endl; }
else if (item == 204) {
cout << " Sticky Barb" << endl; } 
else if (item == 205) {
cout << " Stone Plate" << endl; }
else if (item == 206) {
cout << " Tamato Berry" << endl; }
else if (item == 207) {
cout << " Tanga Berry" << endl; } 
else if (item == 208) {
cout << " Thick Club" << endl; } 
else if (item == 209) {
cout << " Timer Ball" << endl; } 
else if (item == 210) {
cout << " Toxic Orb" << endl; } 
else if (item == 211) {
cout << " Toxic Plate" << endl; } 
else if (item == 212) {
cout << " Twited Spoon" << endl; } 
else if (item == 213) {
cout << " Ultra Ball" << endl; } 
else if (item == 214) {
cout << " Wacan Berry" << endl; } 
else if (item == 215) {
cout << " Water Gem" << endl; }
else if (item == 216) {
cout << " Watmel Berry" << endl; } 
else if (item == 217) {
cout << " Wave Incense" << endl; } 
else if (item == 218) {
cout << " Wepear Berry" << endl; } 
else if (item == 219) {
cout << " White Herb" << endl; } 
else if (item == 220) {
cout << " Wide Lens" << endl; } 
else if (item == 221) {
cout << " Wiki Berry" << endl; } 
else if (item == 222) {
cout << " Wise Glasses" << endl; } 
else if (item == 223) {
cout << " Yache Berry" << endl;
} 
else if (item == 224) {
cout << " Zap Plate" << endl;
} 
else if (item == 225) {
cout << " Zoom Lens" << endl; }
int ability;
ability = rand() %164;
ability = ability + 1;
if (ability == 1) {
cout << "Trait: Stench" << endl;
} else if(ability == 2) {
cout << "Trait: Drizzle" << endl;
} else if(ability == 3) {
cout << "Trait: Speed Boost" << endl;
} else if(ability == 4) {
cout << "Trait: Battle Armor" << endl;
} else if(ability == 5) {
cout << "Trait: Sturdy" << endl;
} else if(ability == 6) {
cout << "Trait: Damp" << endl;
} else if(ability == 7) {
cout << "Trait: Limber" << endl;
} else if(ability == 8) {
cout << "Trait: Sand Veil" << endl;
} else if(ability == 9) {
cout << "Trait: Static" << endl;
} else if(ability == 10) {
cout << "Trait: Volt Absorb" << endl;
} else if(ability == 11) {
cout << "Trait: Water Absorb" << endl;
} else if(ability == 12) {
cout << "Trait: Oblivious" << endl;
} else if(ability == 13) {
cout << "Trait: Cloud Nine" << endl;
} else if(ability == 14) {
cout << "Trait: Compoundeyes" << endl;
} else if(ability == 15) {
cout << "Trait: Insomnia" << endl;
} else if(ability == 16) {
cout << "Trait: Coler Change" << endl;
} else if(ability == 17) {
cout << "Trait: Immunity" << endl;
} else if(ability == 18) {
cout << "Trait: Flash Fire" << endl;
} else if(ability == 19) {
cout << "Trait: Shield Dust" << endl;
} else if(ability == 20) {
cout << "Trait: Own Tempo" << endl;
} else if(ability == 21) {
cout << "Trait: Suction Cups" << endl;
} else if(ability == 22) {
cout << "Trait: Intimidate" << endl;
} else if(ability == 23) {
cout << "Trait: Shadow Tag" << endl;
} else if(ability == 24) {
cout << "Trait: Rough Skin" << endl;
} else if(ability == 25) {
cout << "Trait: Wonder Guard" << endl;
} else if(ability == 26) {
cout << "Trait: Levitate" << endl;
} else if(ability == 27) {
cout << "Trait: Effect Spore" << endl;
} else if(ability == 28) {
cout << "Trait: Synchronize" << endl;
} else if(ability == 29) {
cout << "Trait: Clear Body" << endl;
} else if(ability == 30) {
cout << "Trait: Naturel Cure" << endl;
} else if(ability == 31) {
cout << "Trait: Lightningrod" << endl;
} else if(ability == 32) {
cout << "Trait: Serene Grace" << endl;
} else if(ability == 33) {
cout << "Trait: Swift Swim" << endl;
} else if(ability == 34) {
cout << "Trait: Chlorophyll" << endl;
} else if(ability == 35) {
cout << "Trait: Illuminate" << endl;
} else if(ability == 36) {
cout << "Trait: Trace" << endl;
} else if(ability == 37) {
cout << "Trait: Huge Power" << endl;
} else if(ability == 38) {
cout << "Trait: Poison Point" << endl;
} else if(ability == 39) {
cout << "Trait: Inner Focus" << endl;
} else if(ability == 40) {
cout << "Trait: Magma Armor" << endl;
} else if(ability == 41) {
cout << "Trait: Water Veil" << endl;
} else if(ability == 42) {
cout << "Trait: Magnet Pull" << endl;
} else if(ability == 43) {
cout << "Trait: Soundproof" << endl;
} else if(ability == 44) {
cout << "Trait: Rain Dish" << endl;
} else if(ability == 45) {
cout << "Trait: Sand Stream" << endl;
} else if(ability == 46) {
cout << "Trait: Pressure" << endl;
} else if(ability == 47) {
cout << "Trait: Thick Fat" << endl;
} else if(ability == 48) {
cout << "Trait: Early Bird" << endl;
} else if(ability == 49) {
cout << "Trait: Flame Body" << endl;
} else if(ability == 50) {
cout << "Trait: Run Away" << endl;
} else if(ability == 51) {
cout << "Trait: Keen Eye" << endl;
} else if(ability == 52) {
cout << "Trait: Hyper Cutter" << endl;
} else if(ability == 53) {
cout << "Trait: Pickup" << endl;
} else if(ability == 54) {
cout << "Trait: Truant" << endl;
} else if(ability == 55) {
cout << "Trait: Hustle" << endl;
} else if(ability == 56) {
cout << "Trait: Cute Charm" << endl;
} else if(ability == 57) {
cout << "Trait: Plus" << endl;
} else if(ability == 58) {
cout << "Trait: Minus" << endl;
} else if(ability == 59) {
cout << "Trait: Forecast" << endl;
} else if(ability == 60) {
cout << "Trait: Sticky Hold" << endl;
} else if(ability == 61) {
cout << "Trait: Shed Skin" << endl;
} else if(ability == 62) {
cout << "Trait: Guts" << endl;
} else if(ability == 63) {
cout << "Trait: Marvel Scale" << endl;
} else if(ability == 64) {
cout << "Trait: Liquid Ooze" << endl;
} else if(ability == 65) {
cout << "Trait: Overgrow" << endl;
} else if(ability == 66) {
cout << "Trait: Blaze" << endl;
} else if(ability == 67) {
cout << "Trait: Torrent" << endl;
} else if(ability == 68) {
cout << "Trait: Swarm" << endl;
} else if(ability == 69) {
cout << "Trait: Rock Head" << endl;
} else if(ability == 70) {
cout << "Trait: Drought" << endl;
} else if(ability == 71) {
cout << "Trait: Arena Trap" << endl;
} else if(ability == 72) {
cout << "Trait: Vital Spirit" << endl;
} else if(ability == 73) {
cout << "Trait: White Smoke" << endl;
} else if(ability == 74) {
cout << "Trait: Pure Power" << endl;
} else if(ability == 75) {
cout << "Trait: Shell Armor" << endl;
} else if(ability == 76) {
cout << "Trait: Air Lock" << endl;
} else if(ability == 77) {
cout << "Trait: Tangled Feet" << endl;
} else if(ability == 78) {
cout << "Trait: Motor Drive" << endl;
} else if(ability == 79) {
cout << "Trait: Rivalry" << endl;
} else if(ability == 80) {
cout << "Trait: Steadfast" << endl;
} else if(ability == 81) {
cout << "Trait: Snow Cloak" << endl;
} else if(ability == 82) {
cout << "Trait: Gluttony" << endl;
} else if(ability == 83) {
cout << "Trait: Anger Point" << endl;
} else if(ability == 84) {
cout << "Trait: Unburden" << endl;
} else if(ability == 85) {
cout << "Trait: Heatproof" << endl;
} else if(ability == 86) {
cout << "Trait: Simple" << endl;
} else if(ability == 87) {
cout << "Trait: Dry Skin" << endl;
} else if(ability == 88) {
cout << "Trait: Download" << endl;
} else if(ability == 89) {
cout << "Trait: Iron Fist" << endl;
} else if(ability == 90) {
cout << "Trait: Poison Heal" << endl;
} else if(ability == 91) {
cout << "Trait: Adaptability" << endl;
} else if(ability == 92) {
cout << "Trait: Skill Link" << endl;
} else if(ability == 93) {
cout << "Trait: Hydration" << endl;
} else if(ability == 94) {
cout << "Trait: Solar Power" << endl;
} else if(ability == 95) {
cout << "Trait: Quick Feet" << endl;
} else if(ability == 96) {
cout << "Trait: Normalize" << endl;
} else if(ability == 97) {
cout << "Trait: Sniper" << endl;
} else if(ability == 98) {
cout << "Trait: Magic Guard" << endl;
} else if(ability == 99) {
cout << "Trait: No Guard" << endl;
} else if(ability == 100) {
cout << "Trait: Stall" << endl;
} else if(ability == 101) {
cout << "Trait: Technician" << endl;
} else if(ability == 102) {
cout << "Trait: Leaf Guard" << endl;
} else if(ability == 103) {
cout << "Trait: Klutz" << endl;
} else if(ability == 104) {
cout << "Trait: Mold Breaker" << endl;
} else if(ability == 105) {
cout << "Trait: Super Luck" << endl;
} else if(ability == 106) {
cout << "Trait: Aftermath" << endl;
} else if(ability == 107) {
cout << "Trait: Anticipation" << endl;
} else if(ability == 108) {
cout << "Trait: Forewarn" << endl;
} else if(ability == 109) {
cout << "Trait: Unaware" << endl;
} else if(ability == 110) {
cout << "Trait: Tinted Lens" << endl;
} else if(ability == 111) {
cout << "Trait: Filter" << endl;
} else if(ability == 112) {
cout << "Trait: Slow Start" << endl;
} else if(ability == 113) {
cout << "Trait: Scrappy" << endl;
} else if(ability == 114) {
cout << "Trait: Storm Drain" << endl;
} else if(ability == 115) {
cout << "Trait: Ice Body" << endl;
} else if(ability == 116) {
cout << "Trait: Solid Rock" << endl;
} else if(ability == 117) {
cout << "Trait: Snow Warning" << endl;
} else if(ability == 118) {
cout << "Trait: Honey Gather" << endl;
} else if(ability == 119) {
cout << "Trait: Frisk" << endl;
} else if(ability == 120) {
cout << "Trait: Reckless" << endl;
} else if(ability == 121) {
cout << "Trait: Multitype" << endl;
} else if(ability == 122) {
cout << "Trait: Flower Gift" << endl;
} else if(ability == 123) {
cout << "Trait: Bad Dreams" << endl;
} else if(ability == 124) {
cout << "Trait: Pickpocket" << endl;
} else if(ability == 125) {
cout << "Trait: Sheer Force" << endl;
} else if(ability == 126) {
cout << "Trait: Contrary" << endl;
} else if(ability == 127) {
cout << "Trait: Unnerve" << endl;
} else if(ability == 128) {
cout << "Trait: Defiant" << endl;
} else if(ability == 129) {
cout << "Trait: Defeatist" << endl;
} else if(ability == 130) {
cout << "Trait: Cursed Body" << endl;
} else if(ability == 131) {
cout << "Trait: Healer" << endl;
} else if(ability == 132) {
cout << "Trait: Friend Guard" << endl;
} else if(ability == 133) {
cout << "Trait: Weak Armor" << endl;
} else if(ability == 134) {
cout << "Trait: Heavy Metal" << endl;
} else if(ability == 135) {
cout << "Trait: Light Metal" << endl;
} else if(ability == 136) {
cout << "Trait: Multiscale" << endl;
} else if(ability == 137) {
cout << "Trait: Toxic Boost" << endl;
} else if(ability == 138) {
cout << "Trait: Flare Boost" << endl;
} else if(ability == 139) {
cout << "Trait: Harvest" << endl;
} else if(ability == 140) {
cout << "Trait: Telepathy" << endl;
} else if(ability == 141) {
cout << "Trait: Moody" << endl;
} else if(ability == 142) {
cout << "Trait: Overcoat" << endl;
} else if(ability == 143) {
cout << "Trait: Poison Touch" << endl;
} else if(ability == 144) {
cout << "Trait: Regenerator" << endl;
} else if(ability == 145) {
cout << "Trait: Big Pecks" << endl;
} else if(ability == 146) {
cout << "Trait: Sand Rush" << endl;
} else if(ability == 147) {
cout << "Trait: Wonder Skin" << endl;
} else if(ability == 148) {
cout << "Trait: Analytic" << endl;
} else if(ability == 149) {
cout << "Trait: Illusion" << endl;
} else if(ability == 150) {
cout << "Trait: Imposter" << endl;
} else if(ability == 151) {
cout << "Trait: Infiltrator" << endl;
} else if(ability == 152) {
cout << "Trait: Mummy" << endl;
} else if(ability == 153) {
cout << "Trait: Moxie" << endl;
} else if(ability == 154) {
cout << "Trait: Justified" << endl;
} else if(ability == 155) {
cout << "Trait: Rattled" << endl;
} else if(ability == 156) {
cout << "Trait: Magic Bounce" << endl;
} else if(ability == 157) {
cout << "Trait: Sap Sipper" << endl;
} else if(ability == 158) {
cout << "Trait: Prankster" << endl;
} else if(ability == 159) {
cout << "Trait: Sand Force" << endl;
} else if(ability == 160) {
cout << "Trait: Iron Barbs" << endl;
} else if(ability == 161) {
cout << "Trait: Zen Mode" << endl;
} else if(ability == 162) {
cout << "Trait: Victory Star" << endl;
} else if(ability == 163) {
cout << "Trait: Turboblaze" << endl;
} else if(ability == 164) {
cout << "Trait: Teravolt" << endl;
}
int shine;
shine = rand() %2;
shine = shine + 1;
if (shine == 2){
cout << "Shiny: Yes" << endl;
}
else if (shine == 1) 
{
cout << "Shiny: No" << endl;
}
int EVa;
int EVd;
int EVhp;
int EVsa;
int EVsd;
int EVsp;
int happy;
EVa = rand() %255;
EVa = EVa + 1;
EVd = rand() %255;
EVd = EVd + 1;
EVhp = rand() %255;
EVhp = EVhp + 1;
EVsa = rand() %255;
EVsa = EVsa + 1;
EVsd = rand() %255;
EVsd = EVsd + 1;
EVsp = rand() %255;
EVsp = EVsp + 1;
happy = rand() %255;
happy = happy + 1;
cout << "Happiness: " << happy << endl;
cout << "EVs: " << EVhp << " HP / " << EVa << " Atk / " << EVd << " Def / " << EVsa << " SAtk / " << EVsd << " SDef / " << EVsp << " Spd" << endl;
int nature;
nature = rand() %25;
nature = nature + 1;
 if (nature == 1) {
cout << "Hardy Nature" << endl;
}
else if (nature == 2) {
 cout << "Lonely Nature" << endl;
}
else if (nature == 3) {
cout << "Brave Nature" << endl;
 }
 else if (nature == 4) {
cout << "Adamant Nature" << endl;
} else if (nature == 5) {
cout << "Naughty Nature" << endl;
} else if (nature == 6) {
cout << "Bold Nature" << endl;
} else if (nature == 7) {
cout << "Docile Nature" << endl;
} else if (nature == 8) {
cout << "Relaxed Nature" << endl;
} else if (nature == 9) {
cout << "Impish Nature" << endl;
} else if (nature == 10) {
cout << "Lax Nature" << endl;
} else if (nature == 11) {
cout << "Timid Nature";
} else if (nature == 12) {
cout << "Hasty Nature" << endl;
} else if (nature == 13) {
cout << "Serious Nature" << endl;
} else if (nature == 14) {
cout << "Jolly Nature" << endl;
} else if (nature == 15) {
cout << "Naive Nature" << endl;
} else if (nature == 16) {
cout << "Modest Nature" << endl;
} else if (nature == 17) {
cout << "Mild Nature" << endl;
} else if (nature == 18) {
cout << "Quiet Nature" << endl;
} else if (nature == 19) {
cout << "Bashful Nature" << endl;
} else if (nature == 20) {
cout << "Rash Nature" << endl;
} else if (nature == 21) {
cout << "Calm Nature" << endl;
} else if (nature == 22) {
cout << "Gentle Nature" << endl;
} else if (nature == 23) {
cout << "Sassy Nature" << endl;
} else if (nature == 24) {
cout << "Careful Nature" << endl;
} else if (nature == 25) {
cout << "QuirkyNature" << endl;
}
count = 0;
while (count < 4)
{
count = count + 1;
if (count == 1){
att44 = 0;
att11 = rand() %575;
att11 = att11 + 1;
}
else if (count == 2) {
att11 = 0;
att22 = rand()%575;
att22 = att22 + 1;
}
else if (count == 3) {
att22 = 0;
att33 = rand() %575;
att33 = att33 + 1;
}
else if (count == 4) {
att33 = 0;
att44 = rand() %575;
att44 = att44 + 1;
}
if (att11 == 1 || att22 == 1 || att33 == 1 || att44 == 1){cout << "-Pound" << endl;
} else if(att11 ==2|| att22 ==2|| att33 ==2|| att44 == 2){cout << "-Karate Chop" << endl;
} else if(att11 == 3|| att22 == 3|| att33 == 3|| att44 == 3){cout << "-DoubleSlap" << endl;
} else if(att11 == 4|| att22 == 4|| att33 == 4|| att44 == 4){cout << "-Comet Punch" << endl;
} else if(att11 == 5 || att22 == 5 || att33 == 5 || att44 == 5){cout << "-Mega Punch" << endl;
} else if(att11 == 6 || att22 == 6 || att33 == 6 || att44 == 6){cout << "-Pay Day" << endl;
} else if(att11 == 7 || att22 == 7 || att33 == 7 || att44 == 7){cout << "-Fire Punch" << endl;
} else if(att11 == 8 || att22 == 8 || att33 == 8 || att44 == 8){cout << "-Ice Punch" << endl;
} else if(att11 == 9 || att22 == 9 || att33 == 9 || att44 == 9){cout << "-ThunderPunch" << endl;
} else if(att11 == 10 || att22 == 10 || att33 == 10 || att44 == 10){cout << "-Scratch" << endl;
} else if(att11 == 567 || att22 == 567 || att33 == 567 || att44 == 567){cout << "-ViceGrip" << endl;
} else if(att11 == 568 || att22 == 568 || att33 == 568 || att44 == 568){cout << "-Guillotine" << endl;
} else if(att11 == 569 || att22 == 569 || att33 == 569 || att44 == 569){cout << "-Razor Wind" << endl;
} else if(att11 == 570 || att22 == 570 || att33 == 570 || att44 == 570){cout << "-Swords Dance" << endl;
} else if(att11 == 571 || att22 == 571 || att33 == 571 || att44 == 571){cout << "-Cut" << endl;
} else if(att11 == 572 || att22 == 572 || att33 == 572 || att44 == 572){cout << "-Gust" << endl;
} else if(att11 == 11 || att22 == 11 || att33 == 11 || att44 == 11){cout << "-Wing Attack" << endl; 
} else if(att11 == 12 || att22 == 12 || att33 == 12 || att44 == 12){ cout << "-Whirlwind" << endl; 
} else if(att11 == 13 || att22 == 13 || att33 == 13 || att44 == 13){ cout << "-Fly" << endl; 
} else if(att11 == 14 || att22 == 14 || att33 == 14 || att44 == 14){ cout << "-Bind" << endl; 
} else if(att11 == 15 || att22 == 15 || att33 == 15 || att44 == 15){ cout << "-Slam" << endl; 
} else if(att11 == 16 || att22 == 16 || att33 == 16 || att44 == 16){ cout << "-Vine Whip" << endl; 
} else if(att11 == 17 || att22 == 17 || att33 == 17 || att44 == 17){ cout << "-Stomp" << endl; 
} else if(att11 == 18 || att22 == 18 || att33 == 18 || att44 == 18){ cout << "-Double Kick" << endl; 
} else if(att11 == 19 || att22 == 19 || att33 == 19 || att44 == 19){ cout << "-Mega Kick" << endl; 
} else if(att11 == 20 || att22 == 20 || att33 == 20 || att44 == 20){ cout << "-Jump Kick" << endl; 
} else if(att11 == 21 || att22 == 21 || att33 == 21 || att44 == 21){ cout << "-Rolling Kick" << endl; 
} else if(att11 == 22 || att22 == 22 || att33 == 22 || att44 == 22){ cout << "-Sand-Attack" << endl; 
} else if(att11 == 23 || att22 == 23 || att33 == 23 || att44 == 23){ cout << "-Headbutt" << endl; 
} else if(att11 == 24 || att22 == 24 || att33 == 24 || att44 == 24){ cout << "-Horn Attack" << endl; 
} else if(att11 == 25 || att22 == 25 || att33 == 25 || att44 == 25){ cout << "-Fury Attack" << endl; 
} else if(att11 == 26 || att22 == 26 || att33 == 26 || att44 == 26){ cout << "-Horn Drill" << endl; 
} else if(att11 == 27 || att22 == 27 || att33 == 27 || att44 == 27){ cout << "-Tackle" << endl; 
} else if(att11 == 28 || att22 == 28 || att33 == 28 || att44 == 28){ cout << "-Body Slam" << endl; 
} else if(att11 == 29 || att22 == 29 || att33 == 29 || att44 == 29){ cout << "-Wrap" << endl; 
} else if(att11 == 30 || att22 == 30 || att33 == 30 || att44 == 30){ cout << "-Take Down" << endl; 
} else if(att11 == 31 || att22 == 31 || att33 == 31 || att44 == 31){ cout << "-Thrash" << endl; 
} else if(att11 == 32 || att22 == 32 || att33 == 32 || att44 == 32){ cout << "-Double-Edge" << endl; 
} else if(att11 == 33 || att22 == 33 || att33 == 33 || att44 == 33){ cout << "-Tail Whip" << endl; 
} else if(att11 == 34 || att22 == 34 || att33 == 34 || att44 == 34){ cout << "-Poison Sting" << endl; 
} else if(att11 == 35 || att22 == 35 || att33 == 35 || att44 == 35){ cout << "-Twineedle" << endl; 
} else if(att11 == 36 || att22 == 36 || att33 == 36 || att44 == 36){ cout << "-Pin Missile" << endl; 
} else if(att11 == 37 || att22 == 37 || att33 == 37 || att44 == 37){ cout << "-Leer" << endl; 
} else if(att11 == 38 || att22 == 38 || att33 == 38 || att44 == 38){ cout << "-Bite" << endl; 
} else if(att11 == 39 || att22 == 39 || att33 == 39 || att44 == 39){ cout << "-Growl" << endl; 
} else if(att11 == 40 || att22 == 40 || att33 == 40 || att44 == 40){ cout << "-Roar" << endl; 
} else if(att11 == 41 || att22 == 41 || att33 == 41 || att44 == 41){ cout << "-Sing" << endl; 
} else if(att11 == 42 || att22 == 42 || att33 == 42 || att44 == 42){ cout << "-Supersonic" << endl; 
} else if(att11 == 43 || att22 == 43 || att33 == 43 || att44 == 43){ cout << "-SonicBoom" << endl; 
} else if(att11 == 44 || att22 == 44 || att33 == 44 || att44 == 44){ cout << "-Disable" << endl; 
} else if(att11 == 45 || att22 == 45 || att33 == 45 || att44 == 45){ cout << "-Acid" << endl; 
} else if(att11 == 46 || att22 == 46 || att33 == 46 || att44 == 46){ cout << "-Ember" << endl; 
} else if(att11 == 47 || att22 == 47 || att33 == 47 || att44 == 47){ cout << "-Flamethrower" << endl; 
} else if(att11 == 48 || att22 == 48 || att33 == 48 || att44 == 48){ cout << "-Mist" << endl; 
} else if(att11 == 49 || att22 == 49 || att33 == 49 || att44 == 49){ cout << "-Water Gun" << endl; 
} else if(att11 == 50 || att22 == 50 || att33 == 50 || att44 == 50){ cout << "-Hydro Pump" << endl; 
} else if(att11 == 51 || att22 == 51 || att33 == 51 || att44 == 51){ cout << "-Surf" << endl; 
} else if(att11 == 52 || att22 == 52 || att33 == 52 || att44 == 52){ cout << "-Ice Beam" << endl; 
} else if(att11 == 53 || att22 == 53 || att33 == 53 || att44 == 53){ cout << "-Blizzard" << endl; 
} else if(att11 == 54 || att22 == 54 || att33 == 54 || att44 == 54){ cout << "-Psybeam" << endl; 
} else if(att11 == 55 || att22 == 55 || att33 == 55 || att44 == 55){ cout << "-BubbleBeam" << endl; 
} else if(att11 == 56 || att22 == 56 || att33 == 56 || att44 == 56){ cout << "-Aurora Beam" << endl; 
} else if(att11 == 57 || att22 == 57 || att33 == 57 || att44 == 57){ cout << "-Hyper Beam" << endl; 
} else if(att11 == 58 || att22 == 58 || att33 == 58 || att44 == 58){ cout << "-Peck" << endl; 
} else if(att11 == 59 || att22 == 59 || att33 == 59 || att44 == 59){ cout << "-Drill Peck" << endl; 
} else if(att11 == 60 || att22 == 60 || att33 == 60 || att44 == 60){ cout << "-Submission" << endl; 
} else if(att11 == 61 || att22 == 61 || att33 == 61 || att44 == 61){ cout << "-Low Kick" << endl; 
} else if(att11 == 62 || att22 == 62 || att33 == 62 || att44 == 62){ cout << "-Counter" << endl; 
} else if(att11 == 63 || att22 == 63 || att33 == 63 || att44 == 63){ cout << "-Seismic Toss" << endl; 
} else if(att11 == 64 || att22 == 64 || att33 == 64 || att44 == 64){ cout << "-Strength" << endl; 
} else if(att11 == 65 || att22 == 65 || att33 == 65 || att44 == 65){ cout << "-Absorb" << endl; 
} else if(att11 == 66 || att22 == 66 || att33 == 66 || att44 == 66){ cout << "-Mega Drain" << endl; 
} else if(att11 == 67 || att22 == 67 || att33 == 67 || att44 == 67){ cout << "-Leech Seed" << endl; 
} else if(att11 == 68 || att22 == 68 || att33 == 68 || att44 == 68){ cout << "-Growth" << endl; 
} else if(att11 == 69 || att22 == 69 || att33 == 69 || att44 == 69){ cout << "-Razor Leaf" << endl; 
} else if(att11 == 70 || att22 == 70 || att33 == 70 || att44 == 70){ cout << "-SolarBeam" << endl; 
} else if(att11 == 71 || att22 == 71 || att33 == 71 || att44 == 71){ cout << "-PoisonPowder" << endl; 
} else if(att11 == 72 || att22 == 72 || att33 == 72 || att44 == 72){ cout << "-Stun Spore" << endl; 
} else if(att11 == 73 || att22 == 73 || att33 == 73 || att44 == 73){ cout << "-Sleep Powder" << endl; 
} else if(att11 == 74 || att22 == 74 || att33 == 74 || att44 == 74){ cout << "-Petal Dance" << endl; 
} else if(att11 == 75 || att22 == 75 || att33 == 75 || att44 == 75){ cout << "-String Shot" << endl; 
} else if(att11 == 76 || att22 == 76 || att33 == 76 || att44 == 76){ cout << "-Dragon Rage" << endl; 
} else if(att11 == 77 || att22 == 77 || att33 == 77 || att44 == 77){ cout << "-Fire Spin" << endl;
} else if(att11 == 78 || att22 == 78 || att33 == 78 || att44 == 78){ cout << "-ThunderShock" << endl; 
} else if(att11 == 79 || att22 == 79 || att33 == 79 || att44 == 79){ cout << "-Thunderbolt" << endl; 
} else if(att11 == 80 || att22 == 80 || att33 == 80 || att44 == 80){ cout << "-Thunder Wave" << endl; 
} else if(att11 == 81 || att22 == 81 || att33 == 81 || att44 == 81){ cout << "-Thunder" << endl; 
} else if(att11 == 82 || att22 == 82 || att33 == 82 || att44 == 82){ cout << "-Rock Throw" << endl; 
} else if(att11 == 83 || att22 == 83 || att33 == 83 || att44 == 83){ cout << "-Earthquake" << endl; 
} else if(att11 == 84 || att22 == 84 || att33 == 84 || att44 == 84){ cout << "-Fissure" << endl; 
} else if(att11 == 85 || att22 == 85 || att33 == 85 || att44 == 85){ cout << "-Dig" << endl; 
} else if(att11 == 86 || att22 == 86 || att33 == 86 || att44 == 86){ cout << "-Toxic" << endl; 
} else if(att11 == 87 || att22 == 87 || att33 == 87 || att44 == 87){ cout << "-Confusion" << endl; 
} else if(att11 == 88 || att22 == 88 || att33 == 88 || att44 == 88){ cout << "-Psychic" << endl; 
} else if(att11 == 89 || att22 == 89 || att33 == 89 || att44 == 89){ cout << "-Hypnosis" << endl; 
} else if(att11 == 90 || att22 == 90 || att33 == 90 || att44 == 90){ cout << "-Meditate" << endl; 
} else if(att11 == 91 || att22 == 91 || att33 == 91 || att44 == 91){ cout << "-Agility" << endl; 
} else if(att11 == 92 || att22 == 92 || att33 == 92 || att44 == 92){ cout << "-Quick Attack" << endl; 
} else if(att11 == 93 || att22 == 93 || att33 == 93 || att44 == 93){ cout << "-Rage" << endl; 
} else if(att11 == 94 || att22 == 94 || att33 == 94 || att44 == 94){ cout << "-Teleport" << endl; 
} else if(att11 == 95 || att22 == 95 || att33 == 95 || att44 == 95){ cout << "-Night Shade" << endl; 
} else if(att11 == 96 || att22 == 96 || att33 == 96 || att44 == 96){ cout << "-Mimic" << endl; 
} else if(att11 == 97 || att22 == 97 || att33 == 97 || att44 == 97){ cout << "-Screech" << endl; 
} else if(att11 == 98 || att22 == 98 || att33 == 98 || att44 == 98){ cout << "-Double Team" << endl; 
} else if(att11 == 99 || att22 == 99 || att33 == 99 || att44 == 99){ cout << "-Recover" << endl; 
} else if(att11 == 100 || att22 == 100 || att33 == 100 || att44 == 100){ cout << "-Harden" << endl; 
} else if(att11 == 101 || att22 == 101 || att33 == 101 || att44 == 101){ cout << "-Minimize" << endl; 
} else if(att11 == 102 || att22 == 102 || att33 == 102 || att44 == 102){ cout << "-SmokeScreen" << endl; 
} else if(att11 == 103 || att22 == 103 || att33 == 103 || att44 == 103){ cout << "-Confuse Ray" << endl; 
} else if(att11 == 104 || att22 == 104 || att33 == 104 || att44 == 104){ cout << "-Withdraw" << endl; 
} else if(att11 == 105 || att22 == 105 || att33 == 105 || att44 == 105){ cout << "-Defense Curl" << endl; 
} else if(att11 == 106 || att22 == 106 || att33 == 106 || att44 == 106){ cout << "-Barrier" << endl; 
} else if(att11 == 107 || att22 == 107 || att33 == 107 || att44 == 107){ cout << "-Light Screen" << endl; 
} else if(att11 == 108 || att22 == 108 || att33 == 108 || att44 == 108){ cout << "-Swift" << endl; 
} else if(att11 == 109 || att22 == 109 || att33 == 109 || att44 == 109){ cout << "-Haze" << endl; 
} else if(att11 == 110 || att22 == 110 || att33 == 110 || att44 == 110){ cout << "-Reflect" << endl; 
} else if(att11 == 111 || att22 == 111 || att33 == 111 || att44 == 111){ cout << "-Focus Energy" << endl; 
} else if(att11 == 112 || att22 == 112 || att33 == 112 || att44 == 112){ cout << "-Bide" << endl; 
} else if(att11 == 113 || att22 == 113 || att33 == 113 || att44 == 113){ cout << "-Metronome" << endl; 
} else if(att11 == 114 || att22 == 114 || att33 == 114 || att44 == 114){ cout << "-Mirror Move" << endl; 
} else if(att11 == 115 || att22 == 115 || att33 == 115 || att44 == 115){ cout << "-Selfdestruct" << endl; 
} else if(att11 == 116 || att22 == 116 || att33 == 116 || att44 == 116){ cout << "-Egg Bomb" << endl; 
} else if(att11 == 117 || att22 == 117 || att33 == 117 || att44 == 117){ cout << "-Lick" << endl; 
} else if(att11 == 118 || att22 == 118 || att33 == 118 || att44 == 118){ cout << "-Smog" << endl; 
} else if(att11 == 119 || att22 == 119 || att33 == 119 || att44 == 119){ cout << "-Sludge" << endl; 
} else if(att11 == 120 || att22 == 120 || att33 == 120 || att44 == 120){ cout << "-Bone Club" << endl; 
} else if(att11 == 121 || att22 == 121 || att33 == 121 || att44 == 121){ cout << "-Fire Blast" << endl; 
} else if(att11 == 122 || att22 == 122 || att33 == 122 || att44 == 122){ cout << "-Waterfall" << endl; 
} else if(att11 == 123 || att22 == 123 || att33 == 123 || att44 == 123){ cout << "-Clamp" << endl; 
} else if(att11 == 124 || att22 == 124 || att33 == 124 || att44 == 124){ cout << "-Skull Bash" << endl; 
} else if(att11 == 125 || att22 == 125 || att33 == 125 || att44 == 125){ cout << "-Spike Cannon" << endl; 
} else if(att11 == 126 || att22 == 126 || att33 == 126 || att44 == 126){ cout << "-Constrict" << endl; 
} else if(att11 == 127 || att22 == 127 || att33 == 127 || att44 == 127){ cout << "-Amnesia" << endl; 
} else if(att11 == 128 || att22 == 128 || att33 == 128 || att44 == 128){ cout << "-Kinesis" << endl; 
} else if(att11 == 129 || att22 == 129 || att33 == 129 || att44 == 129){ cout << "-Softboiled" << endl; 
} else if(att11 == 130 || att22 == 130 || att33 == 130 || att44 == 130){ cout << "-Hi Jump Kick" << endl; 
} else if(att11 == 131 || att22 == 131 || att33 == 131 || att44 == 131){ cout << "-Glare" << endl; 
} else if(att11 == 132 || att22 == 132 || att33 == 132 || att44 == 132){ cout << "-Dream Eater" << endl; 
} else if(att11 == 133 || att22 == 133 || att33 == 133 || att44 == 133){ cout << "-Poison Gas" << endl; 
} else if(att11 == 134 || att22 == 134 || att33 == 134 || att44 == 134){ cout << "-Barrage" << endl; 
} else if(att11 == 135 || att22 == 135 || att33 == 135 || att44 == 135){ cout << "-Leech Life" << endl; 
} else if(att11 == 136 || att22 == 136 || att33 == 136 || att44 == 136){ cout << "-Lovely Kiss" << endl; 
} else if(att11 == 137 || att22 == 137 || att33 == 137 || att44 == 137){ cout << "-Sky Attack" << endl; 
} else if(att11 == 138 || att22 == 138 || att33 == 138 || att44 == 138){ cout << "-Transform" << endl; 
} else if(att11 == 139 || att22 == 139 || att33 == 139 || att44 == 139){ cout << "-Bubble" << endl; 
} else if(att11 == 140 || att22 == 140 || att33 == 140 || att44 == 140){ cout << "-Dizzy Punch" << endl; 
} else if(att11 == 141 || att22 == 141 || att33 == 141 || att44 == 141){ cout << "-Spore" << endl; 
} else if(att11 == 142 || att22 == 142 || att33 == 142 || att44 == 142){ cout << "-Flash" << endl; 
} else if(att11 == 143 || att22 == 143 || att33 == 143 || att44 == 143){ cout << "-Psywave" << endl; 
} else if(att11 == 144 || att22 == 144 || att33 == 144 || att44 == 144){ cout << "-Splash" << endl; 
} else if(att11 == 145 || att22 == 145 || att33 == 145 || att44 == 145){ cout << "-Acid Armor" << endl; 
} else if(att11 == 146 || att22 == 146 || att33 == 146 || att44 == 146){ cout << "-Crabhammer" << endl; 
} else if(att11 == 147 || att22 == 147 || att33 == 147 || att44 == 147){ cout << "-Explosion" << endl; 
} else if(att11 == 148 || att22 == 148 || att33 == 148 || att44 == 148){ cout << "-Fury Swipes" << endl; 
} else if(att11 == 149 || att22 == 149 || att33 == 149 || att44 == 149){ cout << "-Bonemerang" << endl; 
} else if(att11 == 150 || att22 == 150 || att33 == 150 || att44 == 150){ cout << "-Rest" << endl; 
} else if(att11 == 151 || att22 == 151 || att33 == 151 || att44 == 151){ cout << "-Rock Slide" << endl; 
} else if(att11 == 152 || att22 == 152 || att33 == 152 || att44 == 152){ cout << "-Hyper Fang" << endl; 
} else if(att11 == 153 || att22 == 153 || att33 == 153 || att44 == 153){ cout << "-Sharpen" << endl; 
} else if(att11 == 154 || att22 == 154 || att33 == 154 || att44 == 154){ cout << "-Conversion" << endl; 
} else if(att11 == 155 || att22 == 155 || att33 == 155 || att44 == 155){ cout << "-Tri Attack" << endl; 
} else if(att11 == 156 || att22 == 156 || att33 == 156 || att44 == 156){ cout << "-Super Fang" << endl; 
} else if(att11 == 157 || att22 == 157 || att33 == 157 || att44 == 157){ cout << "-Slash" << endl; 
} else if(att11 == 158 || att22 == 158 || att33 == 158 || att44 == 158){ cout << "-Substitute" << endl; 
} else if(att11 == 159 || att22 == 159 || att33 == 159 || att44 == 159){ cout << "-Struggle" << endl; 
} else if(att11 == 160 || att22 == 160 || att33 == 160 || att44 == 160){ cout << "-Sketch" << endl; 
} else if(att11 == 161 || att22 == 161 || att33 == 161 || att44 == 161){ cout << "-Triple Kick" << endl; 
} else if(att11 == 162 || att22 == 162 || att33 == 162 || att44 == 162){ cout << "-Thief" << endl; 
} else if(att11 == 163 || att22 == 163 || att33 == 163 || att44 == 163){ cout << "-Spider Web" << endl; 
} else if(att11 == 164 || att22 == 164 || att33 == 164 || att44 == 164){ cout << "-Mind Reader" << endl; 
} else if(att11 == 165 || att22 == 165 || att33 == 165 || att44 == 165){ cout << "-Nightmare" << endl; 
} else if(att11 == 166 || att22 == 166 || att33 == 166 || att44 == 166){ cout << "-Flame Wheel" << endl; 
} else if(att11 == 167 || att22 == 167 || att33 == 167 || att44 == 167){ cout << "-Snore" << endl; 
} else if(att11 == 168 || att22 == 168 || att33 == 168 || att44 == 168){ cout << "-Curse" << endl; 
} else if(att11 == 169 || att22 == 169 || att33 == 169 || att44 == 169){ cout << "-Flail" << endl; 
} else if(att11 == 170 || att22 == 170 || att33 == 170 || att44 == 170){ cout << "-Conversion 2" << endl; 
} else if(att11 == 171 || att22 == 171 || att33 == 171 || att44 == 171){ cout << "-Aeroblast" << endl; 
} else if(att11 == 172 || att22 == 172 || att33 == 172 || att44 == 172){ cout << "-Cotton Spore" << endl; 
} else if(att11 == 173 || att22 == 173 || att33 == 173 || att44 == 173){ cout << "-Reversal" << endl; 
} else if(att11 == 174 || att22 == 174 || att33 == 174 || att44 == 174){ cout << "-Spite" << endl; 
} else if(att11 == 175 || att22 == 175 || att33 == 175 || att44 == 175){ cout << "-Powder Snow" << endl; 
} else if(att11 == 176 || att22 == 176 || att33 == 176 || att44 == 176){ cout << "-Protect" << endl; 
} else if(att11 == 177 || att22 == 177 || att33 == 177 || att44 == 177){ cout << "-Mach Punch" << endl; 
} else if(att11 == 178 || att22 == 178 || att33 == 178 || att44 == 178){ cout << "-Scary Face" << endl; 
} else if(att11 == 179 || att22 == 179 || att33 == 179 || att44 == 179){ cout << "-Faint Attack" << endl; 
} else if(att11 == 180 || att22 == 180 || att33 == 180 || att44 == 180){ cout << "-Sweet Kiss" << endl; 
} else if(att11 == 181 || att22 == 181 || att33 == 181 || att44 == 181){ cout << "-Belly Drum" << endl; 
} else if(att11 == 182 || att22 == 182 || att33 == 182 || att44 == 182){ cout << "-Sludge Bomb" << endl; 
} else if(att11 == 183 || att22 == 183 || att33 == 183 || att44 == 183){ cout << "-Mud-Slap" << endl; 
} else if(att11 == 184 || att22 == 184 || att33 == 184 || att44 == 184){ cout << "-Octazooka" << endl; 
} else if(att11 == 185 || att22 == 185 || att33 == 185 || att44 == 185){ cout << "-Spikes" << endl; 
} else if(att11 == 186 || att22 == 186 || att33 == 186 || att44 == 186){ cout << "-Zap Cannon" << endl; 
} else if(att11 == 187 || att22 == 187 || att33 == 187 || att44 == 187){ cout << "-Foresight" << endl; 
} else if(att11 == 188 || att22 == 188 || att33 == 188 || att44 == 188){ cout << "-Destiny Bond" << endl; 
} else if(att11 == 189 || att22 == 189 || att33 == 189 || att44 == 189){ cout << "-Perish Song" << endl; 
} else if(att11 == 190 || att22 == 190 || att33 == 190 || att44 == 190){ cout << "-Icy Wind" << endl; 
} else if(att11 == 191 || att22 == 191 || att33 == 191 || att44 == 191){ cout << "-Detect" << endl; 
} else if(att11 == 192 || att22 == 192 || att33 == 192 || att44 == 192){ cout << "-Bone Rush" << endl; 
} else if(att11 == 193 || att22 == 193 || att33 == 193 || att44 == 193){ cout << "-Lock-On" << endl; 
} else if(att11 == 194 || att22 == 194 || att33 == 194 || att44 == 194){ cout << "-Outrage" << endl; 
} else if(att11 == 195 || att22 == 195 || att33 == 195 || att44 == 195){ cout << "-Sandstorm" << endl; 
} else if(att11 == 196 || att22 == 196 || att33 == 196 || att44 == 196){ cout << "-Giga Drain" << endl; 
} else if(att11 == 197 || att22 == 197 || att33 == 197 || att44 == 197){ cout << "-Endure" << endl; 
} else if(att11 == 198 || att22 == 198 || att33 == 198 || att44 == 198){ cout << "-Charm" << endl; 
} else if(att11 == 199 || att22 == 199 || att33 == 199 || att44 == 199){ cout << "-Rollout" << endl; 
} else if(att11 == 200 || att22 == 200 || att33 == 200 || att44 == 200){ cout << "-False Swipe" << endl; 
} else if(att11 == 201 || att22 == 201 || att33 == 201 || att44 == 201){ cout << "-Swagger" << endl; 
} else if(att11 == 202 || att22 == 202 || att33 == 202 || att44 == 202){ cout << "-Milk Drink" << endl; 
} else if(att11 == 203 || att22 == 203 || att33 == 203 || att44 == 203){ cout << "-Spark" << endl; 
} else if(att11 == 204 || att22 == 204 || att33 == 204 || att44 == 204){ cout << "-Fury Cutter" << endl; 
} else if(att11 == 205 || att22 == 205 || att33 == 205 || att44 == 205){ cout << "-Steel Wing" << endl; 
} else if(att11 == 206 || att22 == 206 || att33 == 206 || att44 == 206){ cout << "-Mean Look" << endl; 
} else if(att11 == 207 || att22 == 207 || att33 == 207 || att44 == 207){ cout << "-Attract" << endl; 
} else if(att11 == 208 || att22 == 208 || att33 == 208 || att44 == 208){ cout << "-Sleep Talk" << endl; 
} else if(att11 == 209 || att22 == 209 || att33 == 209 || att44 == 209){ cout << "-Heal Bell" << endl; 
} else if(att11 == 210 || att22 == 210 || att33 == 210 || att44 == 210){ cout << "-Return" << endl; 
} else if(att11 == 211 || att22 == 211 || att33 == 211 || att44 == 211){ cout << "-Present" << endl; 
} else if(att11 == 212 || att22 == 212 || att33 == 212 || att44 == 212){ cout << "-Frustration" << endl; 
} else if(att11 == 213 || att22 == 213 || att33 == 213 || att44 == 213){ cout << "-Safeguard" << endl; 
} else if(att11 == 214 || att22 == 214 || att33 == 214 || att44 == 214){ cout << "-Pain Split" << endl; 
} else if(att11 == 215 || att22 == 215 || att33 == 215 || att44 == 215){ cout << "-Sacred Fire" << endl; 
} else if(att11 == 216 || att22 == 216 || att33 == 216 || att44 == 216){ cout << "-Magnitude" << endl; 
} else if(att11 == 217 || att22 == 217 || att33 == 217 || att44 == 217){ cout << "-DynamicPunch" << endl; 
} else if(att11 == 218 || att22 == 218 || att33 == 218 || att44 == 218){ cout << "-Megahorn" << endl; 
} else if(att11 == 219 || att22 == 219 || att33 == 219 || att44 == 219){ cout << "-DragonBreath" << endl; 
} else if(att11 == 220 || att22 == 220 || att33 == 220 || att44 == 220){ cout << "-Baton Pass" << endl; 
} else if(att11 == 221 || att22 == 221 || att33 == 221 || att44 == 221){ cout << "-Encore" << endl; 
} else if(att11 == 222 || att22 == 222 || att33 == 222 || att44 == 222){ cout << "-Persuit" << endl; 
} else if(att11 == 223 || att22 == 223 || att33 == 223 || att44 == 223){ cout << "-Rapid Spin" << endl; 
} else if(att11 == 224 || att22 == 224 || att33 == 224 || att44 == 224){ cout << "-Sweet Scent" << endl; 
} else if(att11 == 225 || att22 == 225 || att33 == 225 || att44 == 225){ cout << "-Iron Tail" << endl; 
} else if(att11 == 226 || att22 == 226 || att33 == 226 || att44 == 226){ cout << "-Metal Claw" << endl; 
} else if(att11 == 227 || att22 == 227 || att33 == 227 || att44 == 227){ cout << "-Vital Throw" << endl; 
} else if(att11 == 228 || att22 == 228 || att33 == 228 || att44 == 228){ cout << "-Morning Sun" << endl; 
} else if(att11 == 229 || att22 == 229 || att33 == 229 || att44 == 229){ cout << "-Synthesis" << endl; 
} else if(att11 == 230 || att22 == 230 || att33 == 230 || att44 == 230){ cout << "-Moonlight" << endl; 
} else if(att11 == 231 || att22 == 231 || att33 == 231 || att44 == 231){ cout << "-Hidden Power" << endl; 
} else if(att11 == 232 || att22 == 232 || att33 == 232 || att44 == 232){ cout << "-Hidden Power [Electric]" << endl; 
} else if(att11 == 233 || att22 == 233 || att33 == 233 || att44 == 233){ cout << "-Hidden Power [Fighting]" << endl; 
} else if(att11 == 234 || att22 == 234 || att33 == 234 || att44 == 234){ cout << "-Hidden Power [Fire]" << endl; 
} else if(att11 == 235 || att22 == 235 || att33 == 235 || att44 == 235){ cout << "-Hidden Power [Grass]" << endl; 
} else if(att11 == 236 || att22 == 236 || att33 == 236 || att44 == 236){ cout << "-Hidden Power [Ice]" << endl; 
} else if(att11 == 237 || att22 == 237 || att33 == 237 || att44 == 237){ cout << "-Hidden Power [Bug]" << endl; 
} else if(att11 == 238 || att22 == 238 || att33 == 238 || att44 == 238){ cout << "-Hidden Power [Dark]" << endl; 
} else if(att11 == 239 || att22 == 239 || att33 == 239 || att44 == 239){ cout << "-Hidden Power [Dragon]" << endl; 
} else if(att11 == 240 || att22 == 240 || att33 == 240 || att44 == 240){ cout << "-Hidden Power [Flying]" << endl; 
} else if(att11 == 241 || att22 == 241 || att33 == 241 || att44 == 241){ cout << "-Hidden Power [Ghost]" << endl; 
} else if(att11 == 242 || att22 == 242 || att33 == 242 || att44 == 242){ cout << "-Hidden Power [Ground]" << endl; 
} else if(att11 == 243 || att22 == 243 || att33 == 243 || att44 == 243){ cout << "-Hidden Power [Poison]" << endl; 
} else if(att11 == 244 || att22 == 244 || att33 == 244 || att44 == 244){ cout << "-Hidden Power [Psychic]" << endl; 
} else if(att11 == 245 || att22 == 245 || att33 == 245 || att44 == 245){ cout << "-Hidden Power [Rock]" << endl; 
} else if(att11 == 246 || att22 == 246 || att33 == 246 || att44 == 246){ cout << "-Hidden Power [Steel]" << endl; 
} else if(att11 == 247 || att22 == 247 || att33 == 247 || att44 == 247){ cout << "-Hidden Power [Water]" << endl; 
} else if(att11 == 248 || att22 == 248 || att33 == 248 || att44 == 248){ cout << "-Cross Chop" << endl; 
} else if(att11 == 249 || att22 == 249 || att33 == 249 || att44 == 249){ cout << "-Twister" << endl; 
} else if(att11 == 250 || att22 == 250 || att33 == 250 || att44 == 250){ cout << "-Rain Dance" << endl; 
} else if(att11 == 251 || att22 == 251 || att33 == 251 || att44 == 251){ cout << "-Sunny Day" << endl; 
} else if(att11 == 252 || att22 == 252 || att33 == 252 || att44 == 252){ cout << "-Crunch" << endl; 
} else if(att11 == 253 || att22 == 253 || att33 == 253 || att44 == 253){ cout << "-Mirror Coat" << endl; 
} else if(att11 == 254 || att22 == 254 || att33 == 254 || att44 == 254){ cout << "-Psych Up" << endl; 
} else if(att11 == 255 || att22 == 255 || att33 == 255 || att44 == 255){ cout << "-ExtremeSpeed" << endl; 
} else if(att11 == 256 || att22 == 256 || att33 == 256 || att44 == 256){ cout << "-AncientPower" << endl; 
} else if(att11 == 257 || att22 == 257 || att33 == 257 || att44 == 257){ cout << "-Shadow Ball" << endl; 
} else if(att11 == 258 || att22 == 258 || att33 == 258 || att44 == 258){ cout << "-Future Sight" << endl; 
} else if(att11 == 259 || att22 == 259 || att33 == 259 || att44 == 259){ cout << "-Rock Smash" << endl; 
} else if(att11 == 260 || att22 == 260 || att33 == 260 || att44 == 260){ cout << "-Whirlpool" << endl; 
} else if(att11 == 261 || att22 == 261 || att33 == 261 || att44 == 261){ cout << "-Beat Up" << endl; 
} else if(att11 == 262 || att22 == 262 || att33 == 262 || att44 == 262){ cout << "-Fake Out" << endl; 
} else if(att11 == 263 || att22 == 263 || att33 == 263 || att44 == 263){ cout << "-Uproar" << endl; 
} else if(att11 == 264 || att22 == 264 || att33 == 264 || att44 == 264){ cout << "-Stockpile" << endl; 
} else if(att11 == 265 || att22 == 265 || att33 == 265 || att44 == 265){ cout << "-Spit Up" << endl; 
} else if(att11 == 266 || att22 == 266 || att33 == 266 || att44 == 266){ cout << "-Swallow" << endl; 
} else if(att11 == 267 || att22 == 267 || att33 == 267 || att44 == 267){ cout << "-Heat Wave" << endl; 
} else if(att11 == 268 || att22 == 268 || att33 == 268 || att44 == 268){ cout << "-Hail" << endl; 
} else if(att11 == 269 || att22 == 269 || att33 == 269 || att44 == 269){ cout << "-Torment" << endl; 
} else if(att11 == 270 || att22 == 270 || att33 == 270 || att44 == 270){ cout << "-Flatter" << endl; 
} else if(att11 == 271 || att22 == 271 || att33 == 271 || att44 == 271){ cout << "-Will-O-Wisp" << endl; 
} else if(att11 == 272 || att22 == 272 || att33 == 272 || att44 == 272){ cout << "-Memento" << endl; 
} else if(att11 == 273 || att22 == 273 || att33 == 273 || att44 == 273){ cout << "-Facade" << endl; 
} else if(att11 == 274 || att22 == 274 || att33 == 274 || att44 == 274){ cout << "-Focus Punch" << endl; 
} else if(att11 == 275 || att22 == 275 || att33 == 275 || att44 == 275){ cout << "-SmellingSalt" << endl; 
} else if(att11 == 276 || att22 == 276 || att33 == 276 || att44 == 276){ cout << "-Follow Me" << endl; 
} else if(att11 == 277 || att22 == 277 || att33 == 277 || att44 == 277){ cout << "-Nature Power" << endl; 
} else if(att11 == 278 || att22 == 278 || att33 == 278 || att44 == 278){ cout << "-Charge" << endl; 
} else if(att11 == 279 || att22 == 279 || att33 == 279 || att44 == 279){ cout << "-Taunt" << endl; 
} else if(att11 == 280 || att22 == 280 || att33 == 280 || att44 == 280){ cout << "-Helping Hand" << endl; 
} else if(att11 == 281 || att22 == 281 || att33 == 281 || att44 == 281){ cout << "-Trick" << endl; 
} else if(att11 == 282 || att22 == 282 || att33 == 282 || att44 == 282){ cout << "-Role Play" << endl; 
} else if(att11 == 283 || att22 == 283 || att33 == 283 || att44 == 283){ cout << "-Wish" << endl; 
} else if(att11 == 284 || att22 == 284 || att33 == 284 || att44 == 284){ cout << "-Assist" << endl; 
} else if(att11 == 285 || att22 == 285 || att33 == 285 || att44 == 285){ cout << "-Ingrain" << endl;  
} else if(att11 == 287 || att22 == 287 || att33 == 287 || att44 == 287){ cout << "-Superpower" << endl; 
} else if(att11 == 288 || att22 == 288 || att33 == 288 || att44 == 288){ cout << "-Magic Coat" << endl; 
} else if(att11 == 289 || att22 == 289 || att33 == 289 || att44 == 289){ cout << "-Recycle" << endl; 
} else if(att11 == 290 || att22 == 290 || att33 == 290 || att44 == 290){ cout << "-Revenge" << endl; 
} else if(att11 == 291 || att22 == 291 || att33 == 291 || att44 == 291){ cout << "-Brick Break" << endl; 
} else if(att11 == 292 || att22 == 292 || att33 == 292 || att44 == 292){ cout << "-Yawn" << endl; 
} else if(att11 == 293 || att22 == 293 || att33 == 293 || att44 == 293){ cout << "-Knock Off" << endl; 
} else if(att11 == 294 || att22 == 294 || att33 == 294 || att44 == 294){ cout << "-Endeavor" << endl; 
} else if(att11 == 295 || att22 == 295 || att33 == 295 || att44 == 295){ cout << "-Eruption" << endl; 
} else if(att11 == 296 || att22 == 296 || att33 == 296 || att44 == 296){ cout << "-Skill Swap" << endl; 
} else if(att11 == 297 || att22 == 297 || att33 == 297 || att44 == 297){ cout << "-Imprison" << endl; 
} else if(att11 == 298 || att22 == 298 || att33 == 298 || att44 == 298){ cout << "-Refresh" << endl; 
} else if(att11 == 299 || att22 == 299 || att33 == 299 || att44 == 299){ cout << "-Grudge" << endl; 
} else if(att11 == 300 || att22 == 300 || att33 == 300 || att44 == 300){ cout << "-Snatch" << endl; 
} else if(att11 == 301 || att22 == 301 || att33 == 301 || att44 == 301){ cout << "-Secret Power" << endl; 
} else if(att11 == 302 || att22 == 302 || att33 == 302 || att44 == 302){ cout << "-Dive" << endl; 
} else if(att11 == 303 || att22 == 303 || att33 == 303 || att44 == 303){ cout << "-Arm Thrust" << endl; 
} else if(att11 == 304 || att22 == 304 || att33 == 304 || att44 == 304){ cout << "-Camouflage" << endl; 
} else if(att11 == 305 || att22 == 305 || att33 == 305 || att44 == 305){ cout << "-Tail Glow" << endl; 
} else if(att11 == 306 || att22 == 306 || att33 == 306 || att44 == 306){ cout << "-Luster Purge" << endl; 
} else if(att11 == 307 || att22 == 307 || att33 == 307 || att44 == 307){ cout << "-Mist Ball" << endl; 
} else if(att11 == 308 || att22 == 308 || att33 == 308 || att44 == 308){ cout << "-FeatherDance" << endl; 
} else if(att11 == 309 || att22 == 309 || att33 == 309 || att44 == 309){ cout << "-Teeter Dance" << endl; 
} else if(att11 == 310 || att22 == 310 || att33 == 310 || att44 == 310){ cout << "-Blaze Kick" << endl; 
} else if(att11 == 311 || att22 == 311 || att33 == 311 || att44 == 311){ cout << "-Mud Sport" << endl; 
} else if(att11 == 312 || att22 == 312 || att33 == 312 || att44 == 312){ cout << "-Ice Ball" << endl; 
} else if(att11 == 313 || att22 == 313 || att33 == 313 || att44 == 313){ cout << "-Needle Arm" << endl; 
} else if(att11 == 314 || att22 == 314 || att33 == 314 || att44 == 314){ cout << "-Slack Off" << endl; 
} else if(att11 == 315 || att22 == 315 || att33 == 315 || att44 == 315){ cout << "-Hyper Voice" << endl; 
} else if(att11 == 316 || att22 == 316 || att33 == 316 || att44 == 316){ cout << "-Poison Fang" << endl; 
} else if(att11 == 317 || att22 == 317 || att33 == 317 || att44 == 317){ cout << "-Crush Claw" << endl; 
} else if(att11 == 318 || att22 == 318 || att33 == 318 || att44 == 318){ cout << "-Blast Burn" << endl; 
} else if(att11 == 319 || att22 == 319 || att33 == 319 || att44 == 319){ cout << "-Hydro Cannon" << endl; 
} else if(att11 == 320 || att22 == 320 || att33 == 320 || att44 == 320){ cout << "-Meteor Mash" << endl; 
} else if(att11 == 321 || att22 == 321 || att33 == 321 || att44 == 321){ cout << "-Astonish" << endl; 
} else if(att11 == 322 || att22 == 322 || att33 == 322 || att44 == 322){ cout << "-Weather Ball" << endl; 
} else if(att11 == 323 || att22 == 323 || att33 == 323 || att44 == 323){ cout << "-Aromatherapy" << endl; 
} else if(att11 == 324 || att22 == 324 || att33 == 324 || att44 == 324){ cout << "-Fake Tears" << endl; 
} else if(att11 == 325 || att22 == 325 || att33 == 325 || att44 == 325){ cout << "-Air Cutter" << endl; 
} else if(att11 == 326 || att22 == 326 || att33 == 326 || att44 == 326){ cout << "-Overheat" << endl; 
} else if(att11 == 327 || att22 == 327 || att33 == 327 || att44 == 327){ cout << "-Odor Sleuth" << endl; 
} else if(att11 == 328 || att22 == 328 || att33 == 328 || att44 == 328){ cout << "-Rock Tomb" << endl; 
} else if(att11 == 329 || att22 == 329 || att33 == 329 || att44 == 329){ cout << "-Silver Wind" << endl; 
} else if(att11 == 330 || att22 == 330 || att33 == 330 || att44 == 330){ cout << "-Metal Sound" << endl; 
} else if(att11 == 331 || att22 == 331 || att33 == 331 || att44 == 331){ cout << "-GrassWhistle" << endl; 
} else if(att11 == 332 || att22 == 332 || att33 == 332 || att44 == 332){ cout << "-Tickle" << endl; 
} else if(att11 == 333 || att22 == 333 || att33 == 333 || att44 == 333){ cout << "-Cosmic Power" << endl; 
} else if(att11 == 334 || att22 == 334 || att33 == 334 || att44 == 334){ cout << "-Water Spout" << endl; 
} else if(att11 == 335 || att22 == 335 || att33 == 335 || att44 == 335){ cout << "-Signal Beam" << endl; 
} else if(att11 == 336 || att22 == 336 || att33 == 336 || att44 == 336){ cout << "-Shadow Punch" << endl; 
} else if(att11 == 337 || att22 == 337 || att33 == 337 || att44 == 337){ cout << "-Extrasensory" << endl; 
} else if(att11 == 338 || att22 == 338 || att33 == 338 || att44 == 338){ cout << "-Sky Uppercut" << endl; 
} else if(att11 == 339 || att22 == 339 || att33 == 339 || att44 == 339){ cout << "-Sand Tomb" << endl; 
} else if(att11 == 340 || att22 == 340 || att33 == 340 || att44 == 340){ cout << "-Sheer Cold" << endl; 
} else if(att11 == 341 || att22 == 341 || att33 == 341 || att44 == 341){ cout << "-Muddy Water" << endl; 
} else if(att11 == 342 || att22 == 342 || att33 == 342 || att44 == 342){ cout << "-Bullet Seed" << endl; 
} else if(att11 == 343 || att22 == 343 || att33 == 343 || att44 == 343){ cout << "-Aerial Ace" << endl; 
} else if(att11 == 344 || att22 == 344 || att33 == 344 || att44 == 344){ cout << "-Icicle Spear" << endl; 
} else if(att11 == 345 || att22 == 345 || att33 == 345 || att44 == 345){ cout << "-Iron Defense" << endl; 
} else if(att11 == 346 || att22 == 346 || att33 == 346 || att44 == 346){ cout << "-Block" << endl; 
} else if(att11 == 347 || att22 == 347 || att33 == 347 || att44 == 347){ cout << "-Howl" << endl; 
} else if(att11 == 348 || att22 == 348 || att33 == 348 || att44 == 348){ cout << "-Dragon Claw" << endl; 
} else if(att11 == 349 || att22 == 349 || att33 == 349 || att44 == 349){ cout << "-Frenzy Plant" << endl; 
} else if(att11 == 350 || att22 == 350 || att33 == 350 || att44 == 350){ cout << "-Bulk Up" << endl; 
} else if(att11 == 351 || att22 == 351 || att33 == 351 || att44 == 351){ cout << "-Bounce" << endl; 
} else if(att11 == 352 || att22 == 352 || att33 == 352 || att44 == 352){ cout << "-Mud Shot" << endl; 
} else if(att11 == 353 || att22 == 353 || att33 == 353 || att44 == 353){ cout << "-Poison Tail" << endl; 
} else if(att11 == 354 || att22 == 354 || att33 == 354 || att44 == 354){ cout << "-Covet" << endl; 
} else if(att11 == 355 || att22 == 355 || att33 == 355 || att44 == 355){ cout << "-Volt Tackle" << endl; 
} else if(att11 == 356 || att22 == 356 || att33 == 356 || att44 == 356){ cout << "-Magical Leaf" << endl; 
} else if(att11 == 357 || att22 == 357 || att33 == 357 || att44 == 357){ cout << "-Water Sport" << endl; 
} else if(att11 == 358 || att22 == 358 || att33 == 358 || att44 == 358){ cout << "-Calm Mind" << endl; 
} else if(att11 == 359 || att22 == 359 || att33 == 359 || att44 == 359){ cout << "-Leaf Blade" << endl; 
} else if(att11 == 360 || att22 == 360 || att33 == 360 || att44 == 360){ cout << "-Dragon Dance" << endl; 
} else if(att11 == 361 || att22 == 361 || att33 == 361 || att44 == 361){ cout << "-Rock Blast" << endl; 
} else if(att11 == 362 || att22 == 362 || att33 == 362 || att44 == 362){ cout << "-Shock Wave" << endl; 
} else if(att11 == 363 || att22 == 363 || att33 == 363 || att44 == 363){ cout << "-Water Pulse" << endl; 
} else if(att11 == 364 || att22 == 364 || att33 == 364 || att44 == 364){ cout << "-Doom Desire" << endl; 
} else if(att11 == 365 || att22 == 365 || att33 == 365 || att44 == 365){ cout << "-Psycho Boost" << endl; 
} else if(att11 == 366 || att22 == 366 || att33 == 366 || att44 == 366){ cout << "-Roost" << endl; 
} else if(att11 == 367 || att22 == 367 || att33 == 367 || att44 == 367){ cout << "-Gravity" << endl; 
} else if(att11 == 368 || att22 == 368 || att33 == 368 || att44 == 368){ cout << "-Miracle Eye" << endl; 
} else if(att11 == 369 || att22 == 369 || att33 == 369 || att44 == 369){ cout << "-Wake-Up Slap" << endl; 
} else if(att11 == 370 || att22 == 370 || att33 == 370 || att44 == 370){ cout << "-Hammer Arm" << endl; 
} else if(att11 == 371 || att22 == 371 || att33 == 371 || att44 == 371){ cout << "-Gyro Ball" << endl; 
} else if(att11 == 372 || att22 == 372 || att33 == 372 || att44 == 372){ cout << "-Healing Wish" << endl; 
} else if(att11 == 373 || att22 == 373 || att33 == 373 || att44 == 373){ cout << "-Brine" << endl; 
} else if(att11 == 374 || att22 == 374 || att33 == 374 || att44 == 374){ cout << "-Natural Gift" << endl; 
} else if(att11 == 375 || att22 == 375 || att33 == 375 || att44 == 375){ cout << "-Feint" << endl; 
} else if(att11 == 376 || att22 == 376 || att33 == 376 || att44 == 376){ cout << "-Pluck" << endl; 
} else if(att11 == 377 || att22 == 377 || att33 == 377 || att44 == 377){ cout << "-Tailwind" << endl; 
} else if(att11 == 378 || att22 == 378 || att33 == 378 || att44 == 378){ cout << "-Acupressure" << endl; 
} else if(att11 == 379 || att22 == 379 || att33 == 379 || att44 == 379){ cout << "-Metal Burst" << endl; 
} else if(att11 == 380 || att22 == 380 || att33 == 380 || att44 == 380){ cout << "-U-turn" << endl; 
} else if(att11 == 381 || att22 == 381 || att33 == 381 || att44 == 381){ cout << "-Close Combat" << endl; 
} else if(att11 == 382 || att22 == 382 || att33 == 382 || att44 == 382){ cout << "-Payback" << endl; 
} else if(att11 == 383 || att22 == 383 || att33 == 383 || att44 == 383){ cout << "-Assurance" << endl; 
} else if(att11 == 384 || att22 == 384 || att33 == 384 || att44 == 384){ cout << "-Embargo" << endl; 
} else if(att11 == 385 || att22 == 385 || att33 == 385 || att44 == 385){ cout << "-Fling" << endl; 
} else if(att11 == 386 || att22 == 386 || att33 == 386 || att44 == 386){ cout << "-Psycho Shift" << endl; 
} else if(att11 == 387 || att22 == 387 || att33 == 387 || att44 == 387){ cout << "-Trump Card" << endl; 
} else if(att11 == 388 || att22 == 388 || att33 == 388 || att44 == 388){ cout << "-Heal Block" << endl; 
} else if(att11 == 389 || att22 == 389 || att33 == 389 || att44 == 389){ cout << "-Wring Out" << endl; 
} else if(att11 == 390 || att22 == 390 || att33 == 390 || att44 == 390){ cout << "-Power Trick" << endl; 
} else if(att11 == 391 || att22 == 391 || att33 == 391 || att44 == 391){ cout << "-Gastro Acid" << endl; 
} else if(att11 == 392 || att22 == 392 || att33 == 392 || att44 == 392){ cout << "-Lucky Chant" << endl; 
} else if(att11 == 393 || att22 == 393 || att33 == 393 || att44 == 393){ cout << "-Me First" << endl; 
} else if(att11 == 394 || att22 == 394 || att33 == 394 || att44 == 394){ cout << "-Copycat" << endl; 
} else if(att11 == 395 || att22 == 395 || att33 == 395 || att44 == 395){ cout << "-Power Swap" << endl; 
} else if(att11 == 396 || att22 == 396 || att33 == 396 || att44 == 396){ cout << "-Guard Swap" << endl; 
} else if(att11 == 397 || att22 == 397 || att33 == 397 || att44 == 397){ cout << "-Punishment" << endl; 
} else if(att11 == 398 || att22 == 398 || att33 == 398 || att44 == 398){ cout << "-Last Resort" << endl; 
} else if(att11 == 399 || att22 == 399 || att33 == 399 || att44 == 399){ cout << "-Worry Seed" << endl; 
} else if(att11 == 400 || att22 == 400 || att33 == 400 || att44 == 400){ cout << "-Sucker Punch" << endl; 
} else if(att11 == 401 || att22 == 401 || att33 == 401 || att44 == 401){ cout << "-Toxic Spikes" << endl; 
} else if(att11 == 402 || att22 == 402 || att33 == 402 || att44 == 402){ cout << "-Heart Swap" << endl; 
} else if(att11 == 403 || att22 == 403 || att33 == 403 || att44 == 403){ cout << "-Aqua Ring" << endl; 
} else if(att11 == 404 || att22 == 404 || att33 == 404 || att44 == 404){ cout << "-Magnet Rise" << endl; 
} else if(att11 == 405 || att22 == 405 || att33 == 405 || att44 == 405){ cout << "-Flare Blitz" << endl; 
} else if(att11 == 406 || att22 == 406 || att33 == 406 || att44 == 406){ cout << "-Force Palm" << endl; 
} else if(att11 == 407 || att22 == 407 || att33 == 407 || att44 == 407){ cout << "-Aura Sphere" << endl; 
} else if(att11 == 408 || att22 == 408 || att33 == 408 || att44 == 408){ cout << "-Rock Polish" << endl; 
} else if(att11 == 409 || att22 == 409 || att33 == 409 || att44 == 409){ cout << "-Poison Jab" << endl; 
} else if(att11 == 410 || att22 == 410 || att33 == 410 || att44 == 410){ cout << "-Dark Pulse" << endl; 
} else if(att11 == 411 || att22 == 411 || att33 == 411 || att44 == 411){ cout << "-X-Scissor" << endl; 
} else if(att11 == 412 || att22 == 412 || att33 == 412 || att44 == 412){ cout << "-Night Slash" << endl; 
} else if(att11 == 413 || att22 == 413 || att33 == 413 || att44 == 413){ cout << "-Aqua Tail" << endl; 
} else if(att11 == 414 || att22 == 414 || att33 == 414 || att44 == 414){ cout << "-Seed Bomb" << endl; 
} else if(att11 == 415 || att22 == 415 || att33 == 415 || att44 == 415){ cout << "-Air Slash" << endl; 
} else if(att11 == 416 || att22 == 416 || att33 == 416 || att44 == 416){ cout << "-Bug Buzz" << endl; 
} else if(att11 == 417 || att22 == 417 || att33 == 417 || att44 == 417){ cout << "-Dragon Pulse" << endl; 
} else if(att11 == 418 || att22 == 418 || att33 == 418 || att44 == 418){ cout << "-Dragon Rush" << endl; 
} else if(att11 == 419 || att22 == 419 || att33 == 419 || att44 == 419){ cout << "-Power Gem" << endl; 
} else if(att11 == 420 || att22 == 420 || att33 == 420 || att44 == 420){ cout << "-Drain Punch" << endl; 
} else if(att11 == 421 || att22 == 421 || att33 == 421 || att44 == 421){ cout << "-Vacuum Wave" << endl; 
} else if(att11 == 422 || att22 == 422 || att33 == 422 || att44 == 422){ cout << "-Focus Blast" << endl; 
} else if(att11 == 423 || att22 == 423 || att33 == 423 || att44 == 423){ cout << "-Energy Ball" << endl; 
} else if(att11 == 424 || att22 == 424 || att33 == 424 || att44 == 424){ cout << "-Brave Bird" << endl; 
} else if(att11 == 425 || att22 == 425 || att33 == 425 || att44 == 425){ cout << "-Earth Power" << endl; 
} else if(att11 == 426 || att22 == 426 || att33 == 426 || att44 == 426){ cout << "-Switcheroo" << endl; 
} else if(att11 == 427 || att22 == 427 || att33 == 427 || att44 == 427){ cout << "-Giga Impact" << endl; 
} else if(att11 == 428 || att22 == 428 || att33 == 428 || att44 == 428){ cout << "-Nasty Plot" << endl; 
} else if(att11 == 429 || att22 == 429 || att33 == 429 || att44 == 429){ cout << "-Bullet Punch" << endl; 
} else if(att11 == 430 || att22 == 430 || att33 == 430 || att44 == 430){ cout << "-Avalanche" << endl; 
} else if(att11 == 431 || att22 == 431 || att33 == 431 || att44 == 431){ cout << "-Ice Shard" << endl; 
} else if(att11 == 432 || att22 == 432 || att33 == 432 || att44 == 432){ cout << "-Shadow Claw" << endl;
} else if(att11 == 575 || att22 == 575 || att33 == 575 || att44 == 575){ cout << "-Thunder Fang" << endl;
} else if(att11 == 574 || att22 == 574 || att33 == 574 || att44 == 574){ cout << "-Ice Fang" << endl;
} else if(att11 == 573 || att22 == 573 || att33 == 573 || att44 == 573){ cout << "-Fire Fang" << endl;
} else if(att11 == 286 || att22 == 286 || att33 == 286 || att44 == 286){ cout << "-Shadow Sneak" << endl; 
} else if(att11 == 433 || att22 == 433 || att33 == 433 || att44 == 433){ cout << "-Mud Bomb" << endl; 
} else if(att11 == 434 || att22 == 434 || att33 == 434 || att44 == 434){ cout << "-Psycho Cut" << endl; 
} else if(att11 == 435 || att22 == 435 || att33 == 435 || att44 == 435){ cout << "-Zen Headbutt" << endl; 
} else if(att11 == 436 || att22 == 436 || att33 == 436 || att44 == 436){ cout << "-Mirror Shot" << endl; 
} else if(att11 == 437 || att22 == 437 || att33 == 437 || att44 == 437){ cout << "-Flash Cannon" << endl; 
} else if(att11 == 438 || att22 == 438 || att33 == 438 || att44 == 438){ cout << "-Rock Climb" << endl; 
} else if(att11 == 439 || att22 == 439 || att33 == 439 || att44 == 439){ cout << "-Defog" << endl; 
} else if(att11 == 440 || att22 == 440 || att33 == 440 || att44 == 440){ cout << "-Trick Room" << endl; 
} else if(att11 == 441 || att22 == 441 || att33 == 441 || att44 == 441){ cout << "-Draco Meteor" << endl; 
} else if(att11 == 442 || att22 == 442 || att33 == 442 || att44 == 442){ cout << "-Discharge" << endl; 
} else if(att11 == 443 || att22 == 443 || att33 == 443 || att44 == 443){ cout << "-Lava Plume" << endl; 
} else if(att11 == 444 || att22 == 444 || att33 == 444 || att44 == 444){ cout << "-Leaf Storm" << endl; 
} else if(att11 == 445 || att22 == 445 || att33 == 445 || att44 == 445){ cout << "-Power Whip" << endl; 
} else if(att11 == 446 || att22 == 446 || att33 == 446 || att44 == 446){ cout << "-Rock Wrecker" << endl; 
} else if(att11 == 447 || att22 == 447 || att33 == 447 || att44 == 447){ cout << "-Cross Poison" << endl; 
} else if(att11 == 448 || att22 == 448 || att33 == 448 || att44 == 448){ cout << "-Gunk Shot" << endl; 
} else if(att11 == 449 || att22 == 449 || att33 == 449 || att44 == 449){ cout << "-Iron Head" << endl; 
} else if(att11 == 450 || att22 == 450 || att33 == 450 || att44 == 450){ cout << "-Magnet Bomb" << endl; 
} else if(att11 == 451 || att22 == 451 || att33 == 451 || att44 == 451){ cout << "-Stone Edge" << endl; 
} else if(att11 == 452 || att22 == 452 || att33 == 452 || att44 == 452){ cout << "-Captivate" << endl; 
} else if(att11 == 453 || att22 == 453 || att33 == 453 || att44 == 453){ cout << "-Stealth Rock" << endl; 
} else if(att11 == 454 || att22 == 454 || att33 == 454 || att44 == 454){ cout << "-Grass Knot" << endl; 
} else if(att11 == 455 || att22 == 455 || att33 == 455 || att44 == 455){ cout << "-Chatter" << endl; 
} else if(att11 == 456 || att22 == 456 || att33 == 456 || att44 == 456){ cout << "-Judgment" << endl; 
} else if(att11 == 457 || att22 == 457 || att33 == 457 || att44 == 457){ cout << "-Bug Bite" << endl; 
} else if(att11 == 458 || att22 == 458 || att33 == 458 || att44 == 458){ cout << "-Charge Beam" << endl; 
} else if(att11 == 459 || att22 == 459 || att33 == 459 || att44 == 459){ cout << "-Wood Hammer" << endl; 
} else if(att11 == 460 || att22 == 460 || att33 == 460 || att44 == 460){ cout << "-Aqua Jet" << endl; 
} else if(att11 == 461 || att22 == 461 || att33 == 461 || att44 == 461){ cout << "-Attack Order" << endl; 
} else if(att11 == 462 || att22 == 462 || att33 == 462 || att44 == 462){ cout << "-Defend Order" << endl; 
} else if(att11 == 463 || att22 == 463 || att33 == 463 || att44 == 463){ cout << "-Heal Order" << endl; 
} else if(att11 == 464 || att22 == 464 || att33 == 464 || att44 == 464){ cout << "-Head Smash" << endl; 
} else if(att11 == 465 || att22 == 465 || att33 == 465 || att44 == 465){ cout << "-Double Hit" << endl; 
} else if(att11 == 466 || att22 == 466 || att33 == 466 || att44 == 466){ cout << "-Roar of Time" << endl; 
} else if(att11 == 467 || att22 == 467 || att33 == 467 || att44 == 467){ cout << "-Spacial Rend" << endl; 
} else if(att11 == 468 || att22 == 468 || att33 == 468 || att44 == 468){ cout << "-Lunar Dance" << endl; 
} else if(att11 == 469 || att22 == 469 || att33 == 469 || att44 == 469){ cout << "-Crush Grip" << endl; 
} else if(att11 == 470 || att22 == 470 || att33 == 470 || att44 == 470){ cout << "-Magma Storm" << endl; 
} else if(att11 == 471 || att22 == 471 || att33 == 471 || att44 == 471){ cout << "-Dark Void" << endl; 
} else if(att11 == 472 || att22 == 472 || att33 == 472 || att44 == 472){ cout << "-Seed Flare" << endl; 
} else if(att11 == 473 || att22 == 473 || att33 == 473 || att44 == 473){ cout << "-Ominous Wind" << endl; 
} else if(att11 == 474 || att22 == 474 || att33 == 474 || att44 == 474){ cout << "-Shadow Force" << endl; 
} else if(att11 == 475 || att22 == 475 || att33 == 475 || att44 == 475){ cout << "-Hone Claws" << endl; 
} else if(att11 == 476 || att22 == 476 || att33 == 476 || att44 == 476){ cout << "-Wide Guard" << endl; 
} else if(att11 == 477 || att22 == 477 || att33 == 477 || att44 == 477){ cout << "-Guard Split" << endl; 
} else if(att11 == 478 || att22 == 478 || att33 == 478 || att44 == 478){ cout << "-Power Split" << endl; 
} else if(att11 == 479 || att22 == 479 || att33 == 479 || att44 == 479){ cout << "-Wonder Room" << endl; 
} else if(att11 == 480 || att22 == 480 || att33 == 480 || att44 == 480){ cout << "-Psyshock" << endl; 
} else if(att11 == 481 || att22 == 481 || att33 == 481 || att44 == 481){ cout << "-Venoshock" << endl; 
} else if(att11 == 482 || att22 == 482 || att33 == 482 || att44 == 482){ cout << "-Autotomize" << endl; 
} else if(att11 == 483 || att22 == 483 || att33 == 483 || att44 == 483){ cout << "-Rage Powder" << endl; 
} else if(att11 == 484 || att22 == 484 || att33 == 484 || att44 == 484){ cout << "-Telekinesis" << endl; 
} else if(att11 == 485 || att22 == 485 || att33 == 485 || att44 == 485){ cout << "-Magic Room" << endl; 
} else if(att11 == 486 || att22 == 486 || att33 == 486 || att44 == 486){ cout << "-Smack Down" << endl; 
} else if(att11 == 487 || att22 == 487 || att33 == 487 || att44 == 487){ cout << "-Storm Throw" << endl; 
} else if(att11 == 488 || att22 == 488 || att33 == 488 || att44 == 488){ cout << "-Flame Burst" << endl; 
} else if(att11 == 489 || att22 == 489 || att33 == 489 || att44 == 489){ cout << "-Sludge Wave" << endl; 
} else if(att11 == 490 || att22 == 490 || att33 == 490 || att44 == 490){ cout << "-Quiver Dance" << endl; 
} else if(att11 == 491 || att22 == 491 || att33 == 491 || att44 == 491){ cout << "-Heavy Slam" << endl; 
} else if(att11 == 492 || att22 == 492 || att33 == 492 || att44 == 492){ cout << "-Synchronoise" << endl; 
} else if(att11 == 493 || att22 == 493 || att33 == 493 || att44 == 493){ cout << "-Electro Ball" << endl; 
} else if(att11 == 494 || att22 == 494 || att33 == 494 || att44 == 494){ cout << "-Soak" << endl; 
} else if(att11 == 495 || att22 == 495 || att33 == 495 || att44 == 495){ cout << "-Flame Charge" << endl; 
} else if(att11 == 496 || att22 == 496 || att33 == 496 || att44 == 496){ cout << "-Coil" << endl; 
} else if(att11 == 497 || att22 == 497 || att33 == 497 || att44 == 497){ cout << "-Low Sweep" << endl; 
} else if(att11 == 498 || att22 == 498 || att33 == 498 || att44 == 498){ cout << "-Acid Spray" << endl; 
} else if(att11 == 499 || att22 == 499 || att33 == 499 || att44 == 499){ cout << "-Foul Play" << endl; 
} else if(att11 == 500 || att22 == 500 || att33 == 500 || att44 == 500){ cout << "-Simple Beam" << endl; 
} else if(att11 == 501 || att22 == 501 || att33 == 501 || att44 == 501){ cout << "-Entrainment" << endl; 
} else if(att11 == 502 || att22 == 502 || att33 == 502 || att44 == 502){ cout << "-After You" << endl; 
} else if(att11 == 503 || att22 == 503 || att33 == 503 || att44 == 503){ cout << "-Round" << endl; 
} else if(att11 == 504 || att22 == 504 || att33 == 504 || att44 == 504){ cout << "-Echoed Voice" << endl; 
} else if(att11 == 505 || att22 == 505 || att33 == 505 || att44 == 505){ cout << "-Chip Away" << endl; 
} else if(att11 == 506 || att22 == 506 || att33 == 506 || att44 == 506){ cout << "-Clear Smog" << endl; 
} else if(att11 == 507 || att22 == 507 || att33 == 507 || att44 == 507){ cout << "-Stored Power" << endl; 
} else if(att11 == 508 || att22 == 508 || att33 == 508 || att44 == 508){ cout << "-Quick Guard" << endl; 
} else if(att11 == 509 || att22 == 509 || att33 == 509 || att44 == 509){ cout << "-Ally Switch" << endl; 
} else if(att11 == 510 || att22 == 510 || att33 == 510 || att44 == 510){ cout << "-Scald" << endl; 
} else if(att11 == 511 || att22 == 511 || att33 == 511 || att44 == 511){ cout << "-Shell Smash" << endl; 
} else if(att11 == 512 || att22 == 512 || att33 == 512 || att44 == 512){ cout << "-Heal Pulse" << endl; 
} else if(att11 == 513 || att22 == 513 || att33 == 513 || att44 == 513){ cout << "-Hex" << endl; 
} else if(att11 == 514 || att22 == 514 || att33 == 514 || att44 == 514){ cout << "-Sky Drop" << endl; 
} else if(att11 == 515 || att22 == 515 || att33 == 515 || att44 == 515){ cout << "-Shift Gear" << endl; 
} else if(att11 == 516 || att22 == 516 || att33 == 516 || att44 == 516){ cout << "-Circle Throw" << endl; 
} else if(att11 == 517 || att22 == 517 || att33 == 517 || att44 == 517){ cout << "-Incinerate" << endl; 
} else if(att11 == 518 || att22 == 518 || att33 == 518 || att44 == 518){ cout << "-Quash" << endl; 
} else if(att11 == 519 || att22 == 519 || att33 == 519 || att44 == 519){ cout << "-Acrobatics" << endl; 
} else if(att11 == 520 || att22 == 520 || att33 == 520 || att44 == 520){ cout << "-Reflect Type" << endl; 
} else if(att11 == 521 || att22 == 521 || att33 == 521 || att44 == 521){ cout << "-Retaliate" << endl; 
} else if(att11 == 522 || att22 == 522 || att33 == 522 || att44 == 522){ cout << "-Final Gambit" << endl; 
} else if(att11 == 523 || att22 == 523 || att33 == 523 || att44 == 523){ cout << "-Bestow" << endl; 
} else if(att11 == 524 || att22 == 524 || att33 == 524 || att44 == 524){ cout << "-Inferno" << endl; 
} else if(att11 == 525 || att22 == 525 || att33 == 525 || att44 == 525){ cout << "-Water Pledge" << endl; 
} else if(att11 == 526 || att22 == 526 || att33 == 526 || att44 == 526){ cout << "-Fire Pledge" << endl; 
} else if(att11 == 527 || att22 == 527 || att33 == 527 || att44 == 527){ cout << "-Grass Pledge" << endl; 
} else if(att11 == 528 || att22 == 528 || att33 == 528 || att44 == 528){ cout << "-Volt Switch" << endl; 
} else if(att11 == 529 || att22 == 529 || att33 == 529 || att44 == 529){ cout << "-Struggle Bug" << endl; 
} else if(att11 == 530 || att22 == 530 || att33 == 530 || att44 == 530){ cout << "-Bulldoze" << endl; 
} else if(att11 == 531 || att22 == 531 || att33 == 531 || att44 == 531){ cout << "-Frost Breath" << endl; 
} else if(att11 == 532 || att22 == 532 || att33 == 532 || att44 == 532){ cout << "-Dragon Tail" << endl; 
} else if(att11 == 533 || att22 == 533 || att33 == 533 || att44 == 533){ cout << "-Work Up" << endl; 
} else if(att11 == 534 || att22 == 534 || att33 == 534 || att44 == 534){ cout << "-Electroweb" << endl; 
} else if(att11 == 536 || att22 == 536 || att33 == 536 || att44 == 536){ cout << "-Wild Charge" << endl; 
} else if(att11 == 537 || att22 == 537 || att33 == 537 || att44 == 537){ cout << "-Drill Run" << endl;
} else if(att11 == 535 || att22 == 535 || att33 == 535 || att44 == 535){ cout << "-Dual Chop" << endl; 
} else if(att11 == 538 || att22 == 538 || att33 == 538 || att44 == 538){ cout << "-Heart Stamp" << endl; 
} else if(att11 == 539 || att22 == 539 || att33 == 539 || att44 == 539){ cout << "-Horn Leech" << endl; 
} else if(att11 == 540 || att22 == 540 || att33 == 540 || att44 == 540){ cout << "-Sacred Sword" << endl; 
} else if(att11 == 541 || att22 == 541 || att33 == 541 || att44 == 541){ cout << "-Razor Shell" << endl; 
} else if(att11 == 542 || att22 == 542 || att33 == 542 || att44 == 542){ cout << "-Heat Crash" << endl; 
} else if(att11 == 543 || att22 == 543 || att33 == 543 || att44 == 543){ cout << "-Leaf Tornado" << endl; 
} else if(att11 == 544 || att22 == 544 || att33 == 544 || att44 == 544){ cout << "-Steamroller" << endl; 
} else if(att11 == 545 || att22 == 545 || att33 == 545 || att44 == 545){ cout << "-Cotton Guard" << endl; 
} else if(att11 == 546 || att22 == 546 || att33 == 546 || att44 == 546){ cout << "-Night Daze" << endl; 
} else if(att11 == 547 || att22 == 547 || att33 == 547 || att44 == 547){ cout << "-Psystrike" << endl; 
} else if(att11 == 548 || att22 == 548 || att33 == 548 || att44 == 548){ cout << "-Tail Slap" << endl; 
} else if(att11 == 549 || att22 == 549 || att33 == 549 || att44 == 549){ cout << "-Hurricane" << endl; 
} else if(att11 == 550 || att22 == 550 || att33 == 550 || att44 == 550){ cout << "-Head Charge" << endl; 
} else if(att11 == 551 || att22 == 551 || att33 == 551 || att44 == 551){ cout << "-Gear Grind" << endl; 
} else if(att11 == 552 || att22 == 552 || att33 == 552 || att44 == 552){ cout << "-Searing Shot" << endl; 
} else if(att11 == 553 || att22 == 553 || att33 == 553 || att44 == 553){ cout << "-Techno Blast" << endl; 
} else if(att11 == 554 || att22 == 554 || att33 == 554 || att44 == 554){ cout << "-Relic Song" << endl; 
} else if(att11 == 555 || att22 == 555 || att33 == 555 || att44 == 555){ cout << "-Secret Sword" << endl; 
} else if(att11 == 556 || att22 == 556 || att33 == 556 || att44 == 556){ cout << "-Glaciate" << endl; 
} else if(att11 == 557 || att22 == 557 || att33 == 557 || att44 == 557){ cout << "-Bolt Strike" << endl; 
} else if(att11 == 558 || att22 == 558 || att33 == 558 || att44 == 558){ cout << "-Blue Flare" << endl; 
} else if(att11 == 559 || att22 == 559 || att33 == 559 || att44 == 559){ cout << "-Fiery Dance" << endl; 
} else if(att11 == 560 || att22 == 560 || att33 == 560 || att44 == 560){ cout << "-Freeze Shock" << endl; 
} else if(att11 == 561 || att22 == 561 || att33 == 561 || att44 == 561){ cout << "-Ice Burn" << endl; 
} else if(att11 == 562 || att22 == 562 || att33 == 562 || att44 == 562){ cout << "-Snarl" << endl; 
} else if(att11 == 563 || att22 == 563 || att33 == 563 || att44 == 563){ cout << "-Icicle Crash" << endl; 
} else if(att11 == 564 || att22 == 564 || att33 == 564 || att44 == 564){ cout << "-V-create" << endl; 
} else if(att11 == 565 || att22 == 565 || att33 == 565 || att44 == 565){ cout << "-Fusion Flare" << endl; 
} else if(att11 == 566 || att22 == 566 || att33 == 566 || att44 == 566){ cout << "-Fusion Bolt" << endl;
}
}
cout << endl;
while (total == 0){
goto end;    
}
}
}
while (total == 0);{
    end:
cout <<  "done" << endl;
return 0; 
}
}
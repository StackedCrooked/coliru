#/*
 * Soubor:  proj2.c
 * Datum:   01.08.2004 21:45
 * Autor:   David Martinek, martinek@fit.vutbr.cz
 * Projekt: Datumy, projekt è. 2 pro pøedmìt IZP
 * Popis:   Program provádí výpoèet rozdílu mezi dvìmi kalendáøními daty.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>


const unsigned int MAX_YEAR = (unsigned int)(UINT_MAX / 365.25);
// #define MAX_YEAR 11000000


/**
 * Vytiskne na standardní výstup text s nápovìdou.
 */
void printHelp()
{
  printf("Program Datumy - vzorová implementace.\n"
         "Autor: David Martinek (c) 2004\n"
         "Program poèítá rozdíl zadaných kalendáøních dat.\n"
         "Data jsou naèítána ze standardního vstupu ve formátu\n"
         "dd.mm.rrrr-dd.mm.rrrr\n"
         "Rozsah povolených let je 1 - %d\n"
         "Popis parametrù:\n"
         "  -h  Vypí¹e tuto obrazovku s nápovìdou.\n", MAX_YEAR);
}

/**
 * Zpracuje argumenty pøíkazového øádku. Pokud narazí na argument -h, vypí¹e
 * nápovìdu a ukonèí program.
 * @param argc Poèet argumentù.
 * @param argv Pole textových øetìzcù s argumenty.
 */
void doParams(int argc, char *argv[])
{
  if (argc == 2 && strcmp("-h", argv[1]) == 0)
  { // tisk nápovìdy
    printHelp();
    exit(EXIT_SUCCESS); // s tímto opatrnì!
  }
}

/**
 * Struktura pro reprezentaci jediného data.
 */
typedef struct tdate
{
  unsigned int day;
  unsigned int month;
  unsigned int year;
} TDate;

/**
 * Vrací true, pokud je parametr pøestupný rok.
 */
bool isLeapYear(unsigned int year)
{
  return (year % 4 == 0) &&
         ((year % 100 != 0) || (year % 400 == 0));
}

/**
 * Vrací true, pokud je hodnota datumu v poøádku.
 */
bool isDateOk(const TDate *date)
{
  bool ok = date->month > 0 && date->month <= 12 &&
            date->year > 0 && date->year <= MAX_YEAR;
  if (!ok) return false;

  unsigned int maxDay = 31;
  if (isLeapYear(date->year)) 
  {
    if (date->month == 2) maxDay = 29;
  }
  else
  {
    if (date->month == 2) maxDay = 28;
  }

  if (date->month == 4 || date->month == 6 || 
      date->month == 9 || date->month == 11)
  {
    maxDay = 30;
  }

  ok = date->day > 0 && date->day <= maxDay;
  return ok;
  // Poznámka: Normálnì nejsem zastáncem "magických konstant", ale v této funkci
  // jde o natolik bì¾nì pou¾ívané hodnoty, které se navíc nikdy nebudou mìnit 
  // (leda by pøi dal¹ím pøevratu nìkdo pøeèísloval mìsíce), ¾e by tady pojmenované
  // konstanty nepøinesly ¾ádnou zásadní výhodu. Jinak ale platí, ¾e 
}

/**
 * Vrací poèet dnù od zaèátku letopoètu do zaèátku zadaného roku (pøièítá i rok
 * "0", ale potom se poèítá rozdíl, tak¾e to nehraje roli).
 */
unsigned int getDaysToYear(unsigned int year)
{
  year -= 1;  //aktuální rok nechci zapoèítat, ten se zapoèítá jinde
  return year*365 + year/4 - year/100 + year/400;
}

/**
 * Vrátí poèet dnù od zaèátku letopoètu do zadaného data.
 */
unsigned int getDays(const TDate *date)
{
  static const unsigned int daysToMonth[12] =
  {
    0, 
    31, 
    31+28, 
    31+28+31, 
    31+28+31+30,
    31+28+31+30+31,
    31+28+31+30+31+30,
    31+28+31+30+31+30+31,
    31+28+31+30+31+30+31+31,
    31+28+31+30+31+30+31+31+30,
    31+28+31+30+31+30+31+31+30+31,
    31+28+31+30+31+30+31+31+30+31+30
  };
  unsigned int days = getDaysToYear(date->year) + daysToMonth[date->month-1] 
    + date->day;
  
  if (isLeapYear(date->year) && date->month > 2)
  {
    days += 1;
  }

  return days;
}

/** Kódy chyb, které se mohou vyskytnout ve funkci readDates. */
enum terrors
{
  EOK,      /**< Bez chyby. */
  EFORMAT,  /**< Chyba ve formátu vstupního výrazu. */
  EDATE1,   /**< Nesmyslná hodnota prvního datumu. */
  EDATE2,   /**< Nesmyslná hodnota druhého datumu. */
  EUNKNOWN  /**< Neznámá chyba. */
};

/** 
 * Chybová hlá¹ení. Jejich poøadí v poli odpovídá poøadí konstant
 * ve výètu terrors.
 */
const char *EMSG[] =
{
  "V¹e v poøádku.",
  "Chybný formát vstupního výrazu.",
  "První datum má nesmyslnou hodnotu.",
  "Druhé datum má nesmyslnou hodnotu.",
  "Neznámá chyba! Nìco je tragicky ¹patnì!"
};

/**
 * Vytiskne chybové hlá¹ení na chybový výstup. 
 */
void printError(int error)
{
  if (error < EOK || error >= EUNKNOWN) 
    error = EUNKNOWN;
  fprintf(stderr, "Chyba: %s\n", EMSG[error]);
}


/**
 * Pøeète výraz ve vstupním streamu a pøevede jej na dva datumy. Pokud
 * je výraz zadán chybnì, vrátí chybový kód.
 * @param stream Vstupní stream (soubor nebo stdin) ze kterého se bude èíst.
 * @param date1 První datum nalezené v textovém øetìzci. (Pøedávání odkazem.)
 * @param date2 Druhé datum nalezené v textovém øetìzci. (Pøedávání odkazem.)
 * @return Vrací chybový kód z výètu enum terrors.
 */
int readDates(FILE *stream, TDate *date1, TDate *date2)
{
  assert(stream != NULL && date1 != NULL && date2 != NULL);

  int num = fscanf(stream, "%u.%u.%u-%u.%u.%u", 
      &date1->day, &date1->month, &date1->year,
      &date2->day, &date2->month, &date2->year);

  if (num != 6) return EFORMAT; // oèekávám, ¾e fscanf zpracovala 6 polo¾ek
  if (!isDateOk(date1)) return EDATE1;
  if (!isDateOk(date2)) return EDATE2;
  return EOK;
}

/**
 * Odeète dvì data a vrátí poèet dnù mezi tìmito datumy.
 */
unsigned int getDiff(const TDate *date1, const TDate *date2)
{
  unsigned int d1 = getDays(date1);
  unsigned int d2 = getDays(date2);
  return (d1 < d2)? d2 - d1 : d1 - d2;
}


/////////////////////////////////////////////////////
/**
 * Hlavní program.
 */
int main(int argc, char *argv[])
{
  doParams(argc, argv);

  TDate date1, date2;
  int err;

  if ((err = readDates(stdin, &date1, &date2)) != EOK)
  {
    fprintf(stderr, "Chyba pøi naèítání vstupních dat!\n");
    printError(err);
    return EXIT_FAILURE;
  }

//  printf("Datum1: %d.%d.%d\n", date1.day, date1.month, date1.year);
//  printf("Datum2: %d.%d.%d\n", date2.day, date2.month, date2.year);
//  printf("Rozdíl: %u\n", getDiff(date1, date2));
  printf("%u\n", getDiff(&date1, &date2));

  return EXIT_SUCCESS;
}

/* konec souboru proj2.c */



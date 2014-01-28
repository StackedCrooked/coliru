/*
 
   locale
   ------

   A std::locale is a set of facets. A facet is a service like formatting for numbers, dates
   or currencies, string collation, character classification, etc. that vary from country to
   country. Each facet is implemented by a std::locale::facet instance. A locale object is
   an efficient container of the different facets appropriate to get delivered to functions
   making use of this information. The output of the locale command lists some of the facets:
 
   >locale
   LANG=
   LC_COLLATE="en_US.UTF-8"
   LC_CTYPE="en_US.UTF-8"
   LC_MESSAGES="en_US.UTF-8"
   LC_MONETARY="en_US.UTF-8"
   LC_NUMERIC="en_US.UTF-8"
   LC_TIME="en_US.UTF-8"
   LC_ALL="en_US.UTF-8"
   
   Code sensible to cultural differences normally uses default locale instances, allowing for
   easy internationalization. See bellow how to set a global for use throughout a program's
   execution. This way the function:
 
      int std::isalpha(char c)
 
   will use this global locale. There is a second function

      bool std::isalpha(char c, std::locale loc)
 
   that accepts a specific locale.
 
   string vs. wstring
   ------------------
   A string object uses a UTF-8 codification, while a wstring stores each unicode code point.
   See the output of the program bellow and note the failure of isalpha in the string case.

   UTF-8 to wide conversion and back
   ---------------------------------
   See an example below how to convert an UTF-8 encoded std::string into a std::wstring where
   character iterations and classification works properly for some normalization work, and the
   convertion from wstring into a string back.

 
   ACHTUNG!!
   =========
   Code doesn't work in gcc 4.8
 

 */

#include <iostream>
#include <iomanip>
#include <string>
#include <locale>
#include <algorithm>
//#include <codecvt>    // not available in gcc 4.8

std::st
   return 0;
}


---

#include <ogonek/data/ucd.h++>

#include <stddef.h>
#include <algorithm>

extern "C" {
    size_t get_name(unsigned u, char* pstr) {
        auto t = ogonek::ucd::get_name(ogonek::code_point(u));
        auto&& s = t.storage();
        if(pstr) {
            std::copy(s.begin(), s.end(), pstr);
        }
        return s.size();
    }
}

---

module Main where

import Foreign.C.Types(CUInt(..), CChar(..), CSize(..))
import Foreign.Ptr(Ptr, nullPtr)
import Foreign.Marshal.Array(allocaArray)
import Foreign.Marshal.Unsafe(unsafeLocalState)

import Data.Char
import Data.ByteString(packCStringLen)
import qualified Data.Text as T
import qualified Data.Text.Encoding as T
import qualified Data.Text.IO as T

foreign import ccall "get_name" c_get_name :: CUInt -> Ptr CChar -> IO CSize

get_name :: Char -> T.Text
get_name c = unsafeLocalState get_nameIO
    where get_nameIO = do let u = fromIntegral $ ord c
                          size <- fmap fromIntegral $ c_get_name u nullPtr
                          allocaArray size $ \buf ->
                            do c_get_name u buf
                               fmap T.decodeUtf8 $ packCStringLen (buf, size)

main = T.putStrLn $ get_name 'A'
---
Output:

LATIN CAPITAL LETTER A
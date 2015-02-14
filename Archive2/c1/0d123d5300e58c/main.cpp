module Fix () where

import Control.Applicative
import Control.Monad (return, ap, mzero, mplus)
import Text.ParserCombinators.ReadP

instance Applicative ReadP where
    pure = return
    (<*>) = ap

instance Alternative ReadP where
    empty = mzero
    (<|>) = mplus
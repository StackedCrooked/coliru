import Data.Function (on)
import Data.List (sortBy)

data SomeType = HOUSE | FRAME | WATER | WIND | CREST deriving (Show)

main :: IO ()
main = do
    print $ reverse [(HOUSE, 1), (FRAME, 2), (WATER, 3), (WIND, 4), (CREST, 5)]
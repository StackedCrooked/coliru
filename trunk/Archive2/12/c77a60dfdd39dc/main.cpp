import Data.List (maximumBy)
import Data.Function (on)

data MakeUp
    = MakeUp
        { a :: String
        , b :: String
        , c :: Int }
    deriving (Eq, Show)

stuff :: [MakeUp]
stuff = 
    [ (MakeUp "eye liner" "MAC" 250)
    , (MakeUp "foundation" "YSL" 800)
    , (MakeUp "toner" "GIVENCHY" 700)
    , (MakeUp "lip gloss" "BENEFIT" 900)
    , (MakeUp "bronzer" "BENEFIT" 500) ]

listAllSold :: String -> [MakeUp] -> [MakeUp] 
listAllSold nameOfBrand = filter ((== nameOfBrand) . b)

mostSold :: [MakeUp] -> MakeUp
mostSold = maximumBy (compare `on` c)

main :: IO ()
main = do
    print $ listAllSold "BENEFIT" stuff
    print $ mostSold stuff
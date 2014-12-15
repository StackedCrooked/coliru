import Data.List (permutations)

comp :: String -> String -> Bool
comp x = (`elem` permutations x)

main :: IO ()
main = do
    print $ comp "abc" "bca"
    print $ comp "abc" "def"
    print $ comp "" "ag"
    print $ comp "" ""
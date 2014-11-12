data X
    = A { s :: String, i :: Int }
    | B { s :: String, i :: Int }
    deriving (Eq, Show)

main :: IO ()
main = putStr "help"

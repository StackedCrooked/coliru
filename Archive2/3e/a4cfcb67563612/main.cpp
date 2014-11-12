data X
    = A String Int
    | B String Int
    deriving (Eq, Show)

s :: X -> String
s (A string _) = string
s (B string _) = string

i :: X -> Int
i (A _ int) = int
i (B _ int) = int

main :: IO ()
main = putStr "help"

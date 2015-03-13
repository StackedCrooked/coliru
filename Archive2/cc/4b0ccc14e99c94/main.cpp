import Text.Printf

type Title = String
type Year = Int
type Cast = [String]
type Fan = [String]

data Film 
    = Film
        { getTitle :: String
        , getCast :: [String]
        , getYear :: Int
        , getFan :: [String]
        }
    deriving (Eq)
    
instance Show Film where
    show (Film t c y f) = 
        concat  
            [ t, " "
            , show c, " "
            , show y, "\n "
            , show f
            ]

main :: IO ()
main = print $ Film "A" [] 1992 []
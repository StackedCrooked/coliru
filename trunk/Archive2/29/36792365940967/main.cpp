import Text.Printf

type Title = String
type Year = Int
type Cast = [String]
type Fan = [String]

type Film = (Title, Cast, Year, Fan)
    
filmToString :: Film -> String
filmToString (title, cast, year, fan) = printf "%s %s %d\n %s" title cast year fan

main :: IO ()
main = putStrLn $ filmToString ("A", 1992, [], [])
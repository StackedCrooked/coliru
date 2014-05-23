import Data.Maybe (fromMaybe)

entitle :: String -> String
entitle = ("Mr. "++)
    
greeting :: String -> String
greeting = ("Hello "++)

func :: Bool -> Maybe String -> String
func True   = greeting . entitle . fromMaybe ""
func False  = greeting . fromMaybe ""
    
main = do
    putStrLn $ func True (Just "John")
    putStrLn $ func False (Just "John")
    putStrLn $ func False Nothing
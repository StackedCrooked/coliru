import Data.Maybe (fromMaybe)

data Person 
    = Mister String
    | Person String
    deriving (Eq)
    
instance Show Person where
    show (Mister name) = "Mr. " ++ name
    show (Person name) = name

greeting :: Maybe Person -> String
greeting (Just person) = "Hello, " ++ show person
greeting Nothing       = "Hello"
    
main = do
    putStrLn $ greeting (Just $ Mister "John")
    putStrLn $ greeting (Just $ Person "John")
    putStrLn $ greeting Nothing
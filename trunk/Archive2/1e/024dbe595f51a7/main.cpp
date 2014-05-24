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

makePerson :: Bool -> String -> Person
makePerson True  = Mister
makePerson False = Person
    
main = do
    putStrLn $ greeting (Just . makePerson True  $ "John")
    putStrLn $ greeting (Just . makePerson False $ "John")
    putStrLn $ greeting Nothing
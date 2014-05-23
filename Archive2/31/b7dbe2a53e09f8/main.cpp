import Data.Maybe (fromMaybe)

data Person 
    = TitledPerson String
    | UntitledPerson String
    deriving (Eq)
    
instance Show Person where
    show (TitledPerson name)  = "Mr. " ++ name
    show (UntitledPerson name) = name

greeting :: Maybe Person -> String
greeting (Just person) = "Hello, " ++ show person
greeting Nothing       = "Hello"
    
main = do
    putStrLn $ greeting (Just $ TitledPerson "John")
    putStrLn $ greeting (Just $ UntitledPerson "John")
    putStrLn $ greeting Nothing
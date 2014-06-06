data Client = GovOrg     String
            | Company    String Integer Person String
            | Individual Person Bool
            deriving Show

data Person = Person String String Gender
            deriving Show

data Gender = Male | Female | Unknown
            deriving Show

clientName :: Client -> String
clientName (GovOrg name)                         = name
clientName (Company name _ _ _)                  = name
clientName (Individual (Person fName lName _) _) = fName ++ " " ++ lName

main = print $ clientName (Individual (Person "Adam" "Smith" Male) True)
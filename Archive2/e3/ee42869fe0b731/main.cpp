type Base = String

data Nested = Nested {
    nestedA :: Base
} deriving (Eq)

data So = So {
    soA :: Nested,
    soB :: Base
} deriving (Eq)

data OMG = OMG {
    omgA :: So,
    omgB :: Base
} deriving (Eq)

(.^) :: a -> (a -> b) -> b
(.^) = flip ($)

omgSoNested :: OMG
omgSoNested = 
    OMG {
        omgA = So {
            soA = Nested {
                nestedA = "Much"
            },
            soB = "Lens"
        },
        omgB = "Wow"
    }
     
main :: IO ()
main = do
    putStrLn $ omgSoNested .^ omgA .^ soA .^ nestedA
    putStrLn $ omgSoNested .^ omgA .^ soB
    putStrLn $ omgSoNested .^ omgB
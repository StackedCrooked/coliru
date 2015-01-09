import qualified Data.Set as Set

main :: IO ()
main = do
    let a = Set.fromList [1, 2, 3, 4]
    putStrLn $ "Size is " ++ show (Set.size a)
    let b = Set.map (\_ -> 1) a
    putStrLn $ "Woops, size is " ++ show (Set.size b)
    
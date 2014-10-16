h :: IO (a -> Int)
h = return $ (\x -> 1)

main :: IO ()
main = do
    fn <- h
    print $ fn (1 :: Int)
    print $ fn "String"
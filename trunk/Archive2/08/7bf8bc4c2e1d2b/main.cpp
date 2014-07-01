main :: IO ()
main = do
    let x = [a + b | a <- [1, 2], b <- [3, 4]]
    print x
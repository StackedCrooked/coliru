main :: IO ()
main = putStr "ok"

f :: IO (a -> IO String)
f = return $ const getLine

main :: IO ()
main = do
  g <- f
    :: IO (a -> IO String)
  g "String" >>= print
  g 5 >>= print
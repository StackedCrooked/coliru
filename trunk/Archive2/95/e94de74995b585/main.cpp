import Control.Monad (mapM_, replicateM)

main :: IO ()
main = mapM_ putStrLn (replicateM 2 "ab")
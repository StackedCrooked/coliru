import Control.Monad

main :: IO ()
main = do
    mapM_ print $ 
        map (\(x, y) -> x ++ y) $ 
            zip (replicateM 3 ["rmin", "imin", "imax"]) (replicateM 3 ["imin", "imax", "rmax"])
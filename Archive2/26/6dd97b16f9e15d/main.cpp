{- a :: [Double]
a = [     0.0, 
     f m 0 ↑ c!!0 h!!0 w_ave,
     f m 1 ↑ c!!1 h!!1 w_ave,
     f m 2 ↑ c!!2 h!!2 w_ave,
     f m 3 ↑ c!!3 h!!3 w_ave,
     f m 4 ↑ c!!4 h!!4 w_ave,
     f m 5 ↑ c!!5 h!!5 w_ave,
     f m 6 ↑ c!!6 h!!6 w_ave,
     ⋮,
     f m i ↑ c!!i h!!i w_ave,
     ]
-}
     
type OLG = Double   -- these
m  = 123.45         -- are really
w_ave = 123.45      -- not important

f :: OLG -> Int -> Double -> Double -> Double -> Double -> Double
f _ _ _ _ _ _ = 0.42

c, h :: [Double]
c = concat . repeat $ [0..10]
h = concat . repeat $ [11..20]

a' :: Double -> Int -> [Double]
a' pre i = curr : a' curr (i + 1)
    where curr = f m i pre (c!!i) (h!!i) w_ave
     
a :: [Double]
a = 0.0 : (a' 0.0 0)
     
main :: IO ()
main = putStr "ok"
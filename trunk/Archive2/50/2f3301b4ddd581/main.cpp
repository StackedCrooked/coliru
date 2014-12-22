{-# LANGUAGE RankNTypes, ImpredicativeTypes, GADTs #-}

a :: (forall char. (char ~ Char) => char, forall num. (Num num) => num)
a = ('a', 1)

main :: IO ()
main = print "ok"
headOr :: a -> [a] -> a
headOr x [] = x
headOr x (y:_) = y

tailOr :: [a] -> [a] -> [a]
tailOr x [] = x
tailOr x (_:ys) = ys

addLnat :: (Integral a) => [a] -> [a] -> [a]
addLnat x y = addLnatAux x y 0
    where addLnatAux :: (Integral a) => [a] -> [a] -> a -> [a]
          addLnatAux [] [] 0 = []
          addLnatAux x y r = rem s 10 : o
              where s = headOr 0 x + headOr 0 y + r
                    o = addLnatAux (tailOr [] x) (tailOr [] y) (quot s 10)

main :: IO ()
main = do
    print $ addLnat [3, 2, 1] [6, 6, 9]
    print $ addLnat [0] [0]
    print $ addLnat [7, 6, 5, 4, 3, 2, 1] [6]
    print $ addLnat [8, 9, 9, 9, 9, 9, 9] [2]
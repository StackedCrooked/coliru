data X = X { a :: Int, b :: Int } deriving Show

func :: X -> X
func x = x {a = 0}

main = print $ func (X {a = 1, b = 2})
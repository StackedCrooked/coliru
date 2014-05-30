{-# LANGUAGE ExistentialQuantification #-}
{-# LANGUAGE RankNTypes #-}

type ShowList = forall a. Show a => [a]

list :: ShowList
list = [42, "lol", 3.14]

main = mapM_ print list
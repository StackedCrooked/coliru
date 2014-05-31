{-# LANGUAGE ExistentialQuantification #-}

data ShowBox = forall a. Show a => ShowBox a
list = [ShowBox 42, ShowBox "hi", ShowBox 3.14]

instance Show ShowBox where
    show (ShowBox a) = show a

main = mapM_ print list
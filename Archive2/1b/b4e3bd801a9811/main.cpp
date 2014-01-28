main =  loop 0 []
  where
    loop n as = do
          a <- gets
          loop (n+1) a:as
    loop 100500 as = return as
class FunctionVoidVoid f where
  call :: f -> ()
  
instance FunctionVoidVoid (() -> a) where
  call f = f () `seq` ()

main = print $ call $ \() -> 42
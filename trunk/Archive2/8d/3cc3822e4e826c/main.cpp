class Typeable a => Resolvable a where
  resolve :: (forall b. Resolvable b => SymbolTable -> b -> b)
          -> SymbolTable -> a -> a

newtype SymbolTable = SymbolTable (forall a. Map Integer (Resolvable a))

main = putStrLn "Lollipop"
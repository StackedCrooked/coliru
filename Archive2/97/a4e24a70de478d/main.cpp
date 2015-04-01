quicksort :: [String]->[String]
quicksort [] = []
quicksort (h:t) = quicksort small ++ (h : quicksort(large))
   where
      small = [y | y <- t, y <= h]
      large = [y | y <- t, y > h]

main = mapM_ print $ quicksort ["foo", "bar", "baz", "lern to test your code"]

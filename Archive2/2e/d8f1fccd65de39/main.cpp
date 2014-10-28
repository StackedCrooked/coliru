data A = A B Int
data B = B Int Int

foo (A (B x y) z) = x + y + z

main = print $ foo (A (B 3 8) 5)
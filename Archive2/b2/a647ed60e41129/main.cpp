data Test = Test String deriving (Eq, Show)

(>:) :: Test -> Test -> Test
(Test a) >: (Test b) = Test $ "(" ++ a ++ " >: " ++ b ++ ")"

infixr 6 >:

(<:) :: Test -> Test -> Test
(Test a) <: (Test b) = Test $ "(" ++ a ++ " <: " ++ b ++ ")"

infixl 6 <:

(?:) :: Test -> Test -> Test
(Test a) ?: (Test b) = Test $ "(" ++ a ++ " ?: " ++ b ++ ")"

infix 6 ?:


main :: IO ()
main = do
    print $ (Test "1") >: (Test "2") >: (Test "4")
    print $ (Test "1") <: (Test "2") <: (Test "4")
    print $ (Test "1") ?: ((Test "2") ?: (Test "4"))
module Main where

import Control.Applicative

import Text.ParserCombinators.ReadP

import Data.Char                (isAlpha)

import System.IO                (hPutStrLn, stderr)
import System.Environment       (getProgName, getArgs)
import System.Exit              (exitFailure)
import Text.Printf              (printf)

-- According to the docs ReadP is an Alternative but this is not borne out in the source
-- so I put a fix away in another module
import Fix ()

-- Also ReadP is some sort of Parsec-lite so we have to roll some stuff ourselves, too
lexeme p = skipSpaces *> p <* skipSpaces

type Var = String

data Expr = EVar Var | ENot Expr | EAnd Expr Expr | EXor Expr Expr | EOr Expr Expr
    deriving (Show)

-- parse [ _val = action(_1, _2) ]
-- ==> (\arg1 arg2 -> action) <$> parse

exprP = orP

orP  = (\arg1 arg2 -> EOr arg1 arg2) <$> xorP <* string "or" <*> xorP
    <|> xorP
   
xorP = (\arg1 arg2 -> EXor arg1 arg2) <$> andP <* string "xor" <*> andP
    <|> andP
        
andP = EAnd <$> notP <* string "and" <*> notP
    <|> notP
        
notP = ENot <$> (string "not" *> simpleP)
    <|> simpleP

simpleP = lexeme (between (char '(') (char ')') exprP)
    <|> varP

varP = lexeme $ EVar <$> munch1 isAlpha

main = do
    arg <- usageOrArgument
    printf "Parsing %s:\n" arg
    print $ [succesful | (succesful, "") <- readP_to_S exprP arg]
    
        where
            usageOrArgument = do
                args <- getArgs
                case args of
                    first:_rest -> return first
                    _ -> usage
                            
            usage = do
                prog <- getProgName
                hPutStrLn stderr $ printf "usage: %s text" prog
                exitFailure
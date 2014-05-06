data Sequence = Sequence { sequenceChar     :: Char
                         , sequenceCount    :: Integer } deriving (Eq, Show)

getNextSequence :: String -> Sequence
getNextSequence (h : []) = (Sequence h 1)
getNextSequence (h : ss)
    | h == ss = (Sequence h (1 + cns))
        where ns    = getNextSequence ss
              cns   = sequenceCount ns
    | otherwise = (Sequence h 1)
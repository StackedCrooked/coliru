p_message = do
  sender <- optional p_prefix
  scmd <- p_command <?> "server command"
  p_space
  params <- p_params <?> "command params"
  eof
  return $ (scmd, Msg sender params)

p_prefix = char ':' *> (try p_host <|> p_identity) <* p_space

p_identity = do
  n <- p_nick
  u <- option "" $ char '!' <:> p_user
  h <- option "" $ char '@' <:> p_host
  return $ n ++ u ++ h

p_command = many1 letter <|> count 3 digit

p_params = do
  middle <- many p_middle
  trailing <- optional $ char ':' *> p_trailing
  return $ middle ++ maybe [] (:[]) trailing

p_middle = (noneOf ":" <:> many p_nonWhite)
  <* (p_space <|> eof $> "")

p_trailing = many $ noneOf "\0\r\n"

p_nick = letter <:> many (letter <|> digit <|> p_special)
p_user = many1 p_nonWhite
p_host = fmap concat $ p_hchars <:> many1 (char '.' <:> p_hchars)
p_hchars = many1 $ noneOf ". "
p_space = many1 $ char ' '
p_special = Text.Parsec.oneOf "-[]\\`^{}|"
p_nonWhite = noneOf " \0\r\n"
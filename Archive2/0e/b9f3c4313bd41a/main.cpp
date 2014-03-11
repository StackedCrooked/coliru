// e = x | (x. e) | e e
// v = (x. e)

// Using De-Bruijn Indices, where n is a natural number >= 0
// e = n | (. e) | e e

#include <string>
#include <stdexcept>
#include <iostream>

// evaluates the lambda string "str" (untyped lambda calculus) and returns the 
// result value. Uses De-Bruijn indices
class LambdaParser {
public:
   LambdaParser(const std::string& code)
   :code(code), col(0) {
    
   }

   // returns the '(.' .. ')' wrapping from "abs" and replaces the right number(s) by arg
   std::string evalApp(std::string abs, std::string arg) {  
      std::string ret;
      
      // the number "absLevel" will be replaced by "arg"!
      LambdaParser absp(abs);
      absp.takeChar();
      absp.takeChar(); // "(."
      absp.skipSpace();
      
      int absLevel = 0;
      while(!absp.atEnd()) {
         if(absp.atDigit()) {
            int n = 0;
            for(; absp.atDigit(); absp.takeChar()) {
               n = n * 10  + (absp.currentChar() - '0');
            }
            if(n == absLevel) {
               ret += arg;
            } else {
               ret += std::to_string(n);
            }
            continue;
         }
         if(absp.currentChar() == '(') {
            absLevel++;
         }
         if(absp.currentChar() == ')') {
            absLevel--;
         }
         ret += absp.currentChar();
         absp.takeChar();
      }
      // erase last ')' and remove trailing space
      ret.resize(ret.size() - 1); 
      while(!ret.empty() && ret.back() == ' ')
         ret.resize(ret.size() - 1);
      return ret;
   }
   
   /// evaluates an abstraction
   std::string evalAbs() {
      skipSpace();
      takeChar('(', "Expected '(.' for lambda abstraction");
      takeChar('.', "Expected '(.' for lambda abstraction");
      
      std::string ret = "(.";
      int parenLevel = 1;
      while(!atEnd()) {
         if(currentChar() == '(') {
            parenLevel++;
         }
         if(currentChar() == ')') {
            parenLevel--;
         }
         ret += currentChar();
         takeChar();
         if(parenLevel == 0)
            break;
      }
      if(parenLevel > 0)
         error("Unmatched ')' for lambda abstraction");
      
      return ret;
   }
   
   // evals a list of "e e ..." outside of an abstraction, which is a list of applications.
   // application is left associative
   std::string evalExpr() {
      skipSpace();
      
      std::string lhs;
      while(!atEnd()) {
         if(currentChar() == '(') {
            if(!lhs.empty()) {
               rewind(evalApp(std::move(lhs), evalAbs()));
               lhs.clear();
            } else {
               lhs = evalAbs();
            }
            skipSpace();
         } else if(currentChar() >= '0' && currentChar() <= '9') {
            error("Unbound(free) variable detected");
         } else {
            error("Unknown syntactic form");
         }
      }
      
      return lhs;
   }
  
private:
   LambdaParser &skipSpace() {
      while(!atEnd()) {
         if(currentChar() != ' ')
            break;
         takeChar();
      }
      return *this;
   }
  
   void rewind(std::string input) {
      code = std::move(input);
      col = 0;
   }
   
   bool atEnd() const {
      return col == code.size();
   }
  
   bool atDigit() const {
      return currentChar() >= '0' && currentChar() <= '9';
   }
      
   void takeChar() {
      if(!atEnd())
         col++;
   }
   
   void takeChar(char expect, const char *errorMessage) {
      if(currentChar() != expect)
         error(errorMessage);
      takeChar();
   }
   
   char currentChar() const {
      return atEnd() ? '\0' : code[col];
   }
   
   int currentCol() const {
      return col;
   }
   
   void error(const std::string& msg) const {
      throw std::runtime_error(
         "error at col " + std::to_string(col + 1) + " in `" + code + "`:\n"
         "   " + msg);
   }
   
private:
   std::string code;
   int col;
};

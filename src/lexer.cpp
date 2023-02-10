#include <cctype> // needed for checking what the char is
#include <cstdio> // needed for getchar
#include <cstdlib> // needed for the conversion
#include <string>

#include "lexer.hpp"

namespace kaleidoscope
{
  static std::string IdentifierString; // filled in if tok_identifier
  static double NumValue; // filled in if tok_number - kaleidoscope represents every number as a double


  static int gettok() {
    static int LastChar = ' ';

    // skip whilst any whitespace
    while (isspace(LastChar)) {
      LastChar = getchar();
    }

    if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
      IdentifierStr = LastChar;

      while (isalnum((LastChar = getchar()))) {
        IdentifierStr += LastChar;
      }

      if (IdentifierStr == "def") {
        return tok_def;
      }

      if (IdentifierStr == "extern") {
        return tok_extern;
      }

      return tok_identifier;
    }

    if (isdigit(LastChar) || LastChar == '.') {
      std::string NumStr;
      do {
        NumStr += LastChar;
	LastChar = getchar();
      } while(isdigit(LastChar) || LastChar == '.');

      NumVal = strtod(NumStr.c_str(), 0);
      return tok_number;
    }

    if (LastChar == '#') {
      // comment so ignore all chars to the end of line
      do {
        LastChar = getchar();
      } while(LastChar != EOF && LastChar != '\n' && LastChar != '\r');

      if (LastChar != EOF) {
        return gettok();
      }
    }


    if (LastChar == EOF) {
      return tok_eof;
    }

    int ThisChar = LastChar;
    LastChar = getchar();

    return ThisChar;
  }
}


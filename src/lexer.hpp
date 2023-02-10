
namespace kaleidescope
{
  // If the lexer doesn't understand a character then it
  // returns it's ascii value so all tokens will be less
  // than 0 to allow for this return
  enum Token {
    tok_eof = -1,

    // commands
    tok_def = -2,
    tok_extern = -3,

    // primary
    tok_identifier = -4,
    tok_number = -5
  };
}


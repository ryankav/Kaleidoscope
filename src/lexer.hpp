#include <memory>
#include <string>
#include <vector>

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

  class ExprAST
  {
  public:
    virtual ~ExprAST() = default;
  };

  // expression for numeric literals
  class NumberExprAST : public ExprAST
  {
    double val;
  
  public:
    NumberExprAST(double);
  };

  // expression for referncing a variable
  class VariableExprAST : public ExprAST
  {
    std::string name;

  public:
    VariableExprAST(std::string const&);
  };

  // expression for a binary operator
  class BinaryExprAST : public ExprAST
  {
    char op;
    std::unique_ptr<ExprAST> LHS, RHS;

  public:
    BinaryExprAST(char, std::unique_ptr<ExprAST>, std::unique_ptr<ExprAST>);
  };

  // expression for function calls
  class CallExprAST : public ExprAST
  {
    std::string callee;
    std::vector<std::unique_ptr<ExprAST>> args;

  public:
    CallExprAST(std::string const&,std::vector<std::unique_ptr<ExprAST>>);
  };

  // Need a prototype for what a function definition is.
  // This captures the functions names and it's arguments

  class PrototypeAST
  {
    std::string name;
    std::vector<std::string> args;
  
  public:
    PrototypeAST(std::string const&, std::vector<std::string>);

    std::string const& getName() const;
  };

  // Node for defining a function definition
  class FunctionAST
  {
    std::unique_ptr<PrototypeAST> proto;
    std::unique_ptr<ExprAST> Body;

  public:
    FunctionAST(std::unique_ptr<PrototypeAST>, std::unique_ptr<ExprAST>);
  };
}


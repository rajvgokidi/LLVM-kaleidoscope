#include <string>

//lexer returns tokens [0-255] ASCII value if it is an unknown character, otherwise one of these for known things
enum Token {
  tok_eof = -1,
  
  // commands
  tok_def = -2,
  tok_extern = -3,

  //primary
  tok_identifier = -4,
  tok_number = -5,
};

static std::string IdentifierStr;
static double NumVal;

static int gettok() {
  static int LastChar = ' ';

  while(isspace(LastChar))
    LastChar = getchar();
  
  if(isalpha(LastChar)) { // checks if char is alphabetic letter
    IdentifierStr = LastChar;
    while (isalnum(LastChar = getchar()))
      IdentifierStr += LastChar;
    if (IdentifierStr == "def")
      return tok_def;
    if (IdentifierStr == "extern")
      return tok_extern;
    return tok_identifier;
  }

  if(isdigit(LastChar) || LastChar == '.') { // checks if char is number
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

    NumVal = strtod(NumStr.c_str(), 0);
    return tok_number;
  }
  
  if (LastChar == '#') { // # represents comments in kal
    do
      LastChar = getchar();
    while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF)
      return gettok();
  }

  if (LastChar == EOF)
    return tok_eof;

  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;
}

class ExprAST {
  public:
    virtual ~ExprAST() = default;
};

class NumberExprAST : public ExprAST {
  double Val;

public:
  NumberExprAST(double Val) : Val(Val) {}
}



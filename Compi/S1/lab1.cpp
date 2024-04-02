#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;

class Token {
public:
  enum Type {PLUS, MINUS, NUM, ERR, END};
  Type type;
  string text;
  
  Token(Type type): type(type) { text = "";};

  Token(Type, char c): type(type) { text = c;};

  Token(Type, const string& source, int first, int last): type(type) {
    text = source.substr(first, last);
  }
};

ostream& operator <<(ostream& outs, const Token& tok) {
  if (tok.text.empty())
    return outs << tok.type;
  else
    // return outs << tok.type << "(" << tok.text << ")";
    return outs << "TOK" << "(" << tok.text << ")";
}

ostream& operator <<(ostream& outs, const Token* tok){
  return outs << *tok;
}

class Scanner {
private:
  string input;
  int first, current;
public:
  Scanner(const char* s): input(s), first(0), current(0) {};

  Token* nextToken(){
    Token* token;
    // consume whitespaces
    while (input[current]==' ') current++;
    if (input[current] == '\0') return new Token(Token::END);
    char c  = input[current];
    first = current;
    if (isdigit(c)) {
      current++;
      while (isdigit(input[current]))
        current++;
      token = new Token(Token::NUM,input,first,current-first);
    } else if (strchr("+-", c)) {
      switch(c) {
      case '+': token = new Token(Token::PLUS,c); break;
      case '-': token = new Token(Token::MINUS,c); break;
      default: cout << "No deberia llegar aca" << endl;
      }
      current++;
    } else {
      token = new Token(Token::ERR, c);
      current++;
    }
    return token;
  };

  ~Scanner(){};
};

enum BinaryOp { PLUS, MINUS };

class Exp {
public:
  virtual void print() = 0;
  virtual int eval() = 0;
  virtual ~Exp() = 0;
  static char binopToChar(BinaryOp op);
};


class BinaryExp : public Exp {
public:
  Exp *left, *right;
  BinaryOp op;
  BinaryExp(Exp* l, Exp* r, BinaryOp op);
  void print();
  int eval();
  ~BinaryExp();
};

class NumberExp : public Exp {
public:
  int value; // Atributo entero

  NumberExp(int v); // Constructor

  // Métodos
  void print();
  int eval();

  ~NumberExp(); // Destructor
};

class Parser {
private:
  Scanner* scanner;
  Token *current, *previous;

  bool match(Token::Type ttype){
    if (check(ttype)) {
      advance();
      return true;
    }
    return false;
  }

  bool check(Token::Type ttype);
  bool advance();
  bool isAtEnd();
  Exp* parseExpression();
  Exp* parseTerm();
  Exp* parseFactor();
  bool tokenToOp(Token* tk, BinaryOp& op);
public:
  Parser(Scanner* scanner);
  Exp* parse();
};
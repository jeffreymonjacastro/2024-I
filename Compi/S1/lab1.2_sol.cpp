#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>

#include <fstream>

using namespace std;

class Token {
public:
  enum Type {PLUS, MINUS, MUL, DIV, LPAREN, RPAREN, NUM, ERR, END};
  Type type;
  string text;
  Token(Type);
  Token(Type, char c);
  Token(Type, const string& source, int first, int last);
};

class Scanner {
private:
  string input;
  int first, current;
public:
  Scanner(const char* in_s);
  Token* nextToken();
  ~Scanner();

};

enum BinaryOp { PLUS, MINUS, MUL, DIV };

class Exp {
public:
  virtual void print() = 0;
  virtual int eval() = 0;
  virtual ~Exp() = 0;
  virtual void rpn(ostringstream& str) = 0;
  virtual void genCode(ostringstream& str) = 0;
  static char binopToChar(BinaryOp op);
};


class BinaryExp : public Exp {
public:
  Exp *left, *right;
  BinaryOp op;
  BinaryExp(Exp* l, Exp* r, BinaryOp op);
  void print();
  int eval();
  void rpn(ostringstream& str);
  void genCode(ostringstream& str);  
  ~BinaryExp();
};

class NumberExp : public Exp {
public:
  int value;
  NumberExp(int v);
  void print();
  int eval();
  void rpn(ostringstream& str);
  void genCode(ostringstream& str);
  ~NumberExp();
};

class ParenthExp : public Exp {
public:
  Exp *e;
  ParenthExp(Exp *e);
  void print();
  int eval();
  void rpn(ostringstream& str);
  void genCode(ostringstream& str);
  ~ParenthExp();
};

class Parser {
private:
  Scanner* scanner;
  Token *current, *previous;
  bool match(Token::Type ttype);
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

/* ******** Token definition ********* */

Token::Token(Type type):type(type) { text = ""; }

Token::Token(Type type, char c):type(type) { text = c; }

Token::Token(Type type, const string& source, int first, int last):type(type) {
  text = source.substr(first,last);
}

std::ostream& operator << ( std::ostream& outs, const Token & tok )
{
  if (tok.text.empty())
    return outs << tok.type;
  else
    // return outs << tok.type << "(" << tok.text << ")";
    return outs << "TOK" << "(" << tok.text << ")";
}

std::ostream& operator << ( std::ostream& outs, const Token* tok ) {
  return outs << *tok;
}

/* ******** Scanner definition ********* */

Scanner::Scanner(const char* s):input(s),first(0), current(0) { }

Token* Scanner::nextToken() {
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
  } else if (strchr("+-*/()", c)) {
    switch(c) {
    case '+': token = new Token(Token::PLUS,c); break;
    case '-': token = new Token(Token::MINUS,c); break;
    case '*': token = new Token(Token::MUL,c); break;
    case '/': token = new Token(Token::DIV,c); break;
    case '(': token = new Token(Token::LPAREN,c); break;
    case ')': token = new Token(Token::RPAREN,c); break;
    default: cout << "No deberia llegar aca" << endl;
    }
    current++;
  } else {
    token = new Token(Token::ERR, c);
    current++;
  }
  return token;
}

Scanner::~Scanner() { }

/* ******** Parser definition ********* */

// match and consume next token
bool Parser::match(Token::Type ttype) {
  if (check(ttype)) {
    advance();
    return true;
  }
  return false;
}

bool Parser::check(Token::Type ttype) {
  if (isAtEnd()) return false;
  return current->type == ttype;
}

bool Parser::advance() {
  if (!isAtEnd()) {
    Token* temp =current;
    if (previous) delete previous;
    current = scanner->nextToken();
    previous = temp;
    if (check(Token::ERR)) {
      cout << "Parse error, unrecognised character: " << current->text << endl;
      exit(0);
    }
    return true;
  }
  return false;
} 

bool Parser::isAtEnd() {
  return (current->type == Token::END);
} 

Parser::Parser(Scanner* sc):scanner(sc) {
  previous = current = NULL;
  return;
};

Exp* Parser::parse() {
  // get first token
  current = scanner->nextToken();
  if (check(Token::ERR)) {
      cout << "Error en scanner - caracter invalido" << endl;
      exit(0);
  }
  Exp* exp = parseExpression();
  // cout << "last token: " << current << endl;
  if (current) delete current;
  return exp;
}

Exp* Parser::parseExpression() {

  Exp* left = parseTerm();
  while (match(Token::PLUS) || match(Token::MINUS)) {
    BinaryOp op = (previous->type == Token::PLUS) ? PLUS : MINUS;    
    Exp* right = parseTerm();
    left = new BinaryExp(left, right, op); 
  } 
  return left;
}

Exp* Parser::parseTerm() {
  Exp* left = parseFactor();
  while (match(Token::MUL) || match(Token::DIV)) {
    BinaryOp op = (previous->type == Token::MUL) ? MUL : DIV;    
    Exp* right = parseFactor();
    left = new BinaryExp(left, right, op); 
  } 
  return left;
}

Exp* Parser::parseFactor() {
  if (match(Token::NUM)) {
    return new NumberExp(stoi(previous->text));
  }
  if (match(Token::LPAREN)) {
    Exp *exp = parseExpression();
    if (!match(Token::RPAREN)) {
      cout << "Error: Esperaba parentesis derecho";
      exit(0);
    }
    return new ParenthExp(exp);
  }
  cout << "Error: se esperaba un número." << endl;
  exit(0);
}

bool Parser::tokenToOp(Token* tk, BinaryOp& op)  {
  switch(tk->type) {
  case Token::PLUS: op = PLUS; break;
  case Token::MINUS: op = MINUS; break;
  default: cout << "Invalid Operator" << endl; return false;
  }
  return true;
}

char Exp::binopToChar(BinaryOp op) {
  char  c=' ';
  switch(op) {
  case PLUS: c = '+'; break;
  case MINUS: c = '-'; break;
  case MUL: c = '*'; break;
  case DIV: c = '/'; break; 
  default: c = '$';
  }
  return c;
}

/* ******** Abstract Syntax Tree definition ********* */

// Constructors
BinaryExp::BinaryExp(Exp* l, Exp* r, BinaryOp op):left(l),right(r),op(op) {}
NumberExp::NumberExp(int v):value(v) {}
ParenthExp::ParenthExp(Exp* e):e(e) {}

Exp::~Exp() {}
BinaryExp::~BinaryExp() { delete left; delete right; }
NumberExp::~NumberExp() { }
ParenthExp::~ParenthExp() { delete e; }

void BinaryExp::print() {
  left->print();
  char c = binopToChar(this->op);;
  cout << ' ' << c << ' ';
  right->print();
}

void NumberExp::print() {
  cout << value;
}

void ParenthExp::print() {
  cout << '(';
  e->print();
  cout << ')';
}

int BinaryExp::eval() {
  int v1 = this->left->eval();
  int v2 = this->right->eval();
  int result;
  switch(this->op) {
  case PLUS: result = v1+v2; break;  
  case MINUS: result = v1-v2; break;
  case MUL: result = v1*v2; break;
  case DIV: result = v1/v2; break;
  default:
    cout << "eval: operador desconocido" << endl;
    result = 0;
  }
  return result;
}

int NumberExp::eval() {
  return this->value;
}

int ParenthExp::eval() {
  return this->e->eval();
}

// rpn
void BinaryExp::rpn(ostringstream& str) {
  left->rpn(str);
  right->rpn(str);
  char c = binopToChar(this->op);
  str << c << ' ';
}

void NumberExp::rpn(ostringstream& str) {
  str << value << ' ';
}

void ParenthExp::rpn(ostringstream& str) {
  e->rpn(str);
}


// genCode
void BinaryExp::genCode(ostringstream& str) {
  left->genCode(str);
  right->genCode(str);
  char  c=' ';
  switch(this->op) {
  case PLUS: str << "add"; break;
  case MINUS: str << "sub"; break;
  case MUL: str << "mul"; break;
  case DIV: str << "div"; break;
  }
  str << endl;
}

void NumberExp::genCode(ostringstream& str) {
  str << "push " << value << endl;
}

void ParenthExp::genCode(ostringstream& str) {
  e->genCode(str);
}


// ---------------------------------------------------



void test_scanner(Scanner * scanner) {
  Token* current;
  current = scanner->nextToken();
  while (current->type != Token::END) {
    if (current->type == Token::ERR) {
      cout << "Error en scanner - caracter invalido: " << current->text << endl;
      break;
    } else
      cout << current << endl;
    current = scanner->nextToken();
  }
  exit(1);

}

int main(int argc, const char* argv[]) {
  
  if (argc != 2  && argc != 3) {
    cout << "Incorrect number of arguments" << endl;
    exit(1);
  }

  Scanner scanner(argv[1]);

  //test_scanner(&scanner);
 
  Parser parser(&scanner);

  Exp *exp = parser.parse();

  cout << "expr: ";
  exp->print();
  cout << endl;

  cout << "eval: ";
  cout << exp->eval() << endl;

  std::ostringstream rpn_str;
  exp->rpn(rpn_str);
  cout << "rpn: " << rpn_str.str() << endl;

  std::ostringstream code_str;
  exp->genCode(code_str);

  // output original
  // cout << "---------- stack machine code ------------------" << endl;
  // cout << code_str.str() << endl;

  string outfname;
  if (argc == 2)
    outfname = "out.svm";
  else
    outfname = argv[2];
  cout << "Compiling to: " << outfname << endl;
  
  std::ofstream outfile;
  outfile.open(outfname);
  outfile << code_str.str();
  outfile.close();

  delete exp;  
}

#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <fstream>


using namespace std;

/*
  Scanner and Parser code inspired by code in Crafting Interpreters by Robert Nystrom
*/



class Token {
public:
  enum Type { LPAREN=0, RPAREN, PLUS, MINUS, MULT, DIV, POW, NUM, ERR, END,ID, FLOAT, SIN, COS, COMMENT };
  static const char* token_names[15];
  Type type;
  string lexema;
  Token(Type);
  Token(Type, char c);
  Token(Type, const string source);
};

const char* Token::token_names[15] = { "LPAREN" , "RPAREN", "PLUS", "MINUS", "MULT", "DIV", "POW", "NUM", "ERR", "END" ,"ID","FLOAT", "SIN", "COS", "COMMENT"};

Token::Token(Type type):type(type) { lexema = ""; }

Token::Token(Type type, char c):type(type) { lexema = c; }

Token::Token(Type type, const string source):type(type) {
  lexema = source;
}

std::ostream& operator << ( std::ostream& outs, const Token & tok )
{
  if (tok.lexema.empty())
    return outs << Token::token_names[tok.type];
  else
    return outs << Token::token_names[tok.type] << "(" << tok.lexema << ")";
}

std::ostream& operator << ( std::ostream& outs, const Token* tok ) {
  return outs << *tok;
}


class Scanner {
public:
  Scanner(const char* in_s);
  Token* nextToken();
  ~Scanner();  
private:
  string input;
  int first, current;
  int state;
  char nextChar();
  void rollBack();
  void startLexema();
  string getLexema();
  string getComment();
};

Scanner::Scanner(const char* s):input(s),first(0),current(0) { }

Token* Scanner::nextToken() {
  Token* token;
  char c;
  state = 0;
  startLexema();
  while (1) {
    switch (state) {
    case 0: c = nextChar();
      if (c == ' ') { startLexema(); state = 0; }
      else if (c == '\0') return new Token(Token::END);
      else if (c == '(') state = 1;
      else if (c == ')') state = 2;
      else if (c == '+') state = 3;
      else if (c == '-') state = 4;
      else if (c == '*') state = 5;
      else if (c == '/') state = 6;
      else if (c == '^') state = 7;
      else if (c == 's') state = 14;
      else if (c == 'c') state = 17;
      else if (c == '#') state = 20;
      else if (isdigit(c)) { state = 8; }
      else if (isalpha(c)) { state = 10; }
      else return new Token(Token::ERR, c);
      break;
    case 1: return new Token(Token::LPAREN);
    case 2: return new Token(Token::RPAREN);
    case 3: return new Token(Token::PLUS,c);
    case 4: return new Token(Token::MINUS,c);
    case 5: return new Token(Token::MULT,c);
    case 6: return new Token(Token::DIV,c);
    case 7: return new Token(Token::POW,c);
    case 8: c = nextChar();
      if (isdigit(c)) state = 8;
      else if (c == '.') state = 12;
      else state = 9;
      break;
    case 10: 
      c = nextChar();
      if (isdigit(c) || isalpha(c)) state = 10;
      else state = 11;
      break;
    case 12: c = nextChar();
      if (isdigit(c)) state = 12;
      else state = 13;
      break;
    case 9: rollBack();
      return new Token(Token::NUM, getLexema());
    case 11: rollBack();
      return new Token(Token::ID, getLexema());
    case 13: rollBack();
      return new Token(Token::FLOAT, getLexema());
    case 14:
      c = nextChar();
      if (c == 'i') state = 15;
      else state = 10;
      break;
    case 15:
      c = nextChar();
      if (c == 'n') state = 16;
      else state = 10;
      break;
    case 16:
      return new Token(Token::SIN, getLexema());
    case 17:
      c = nextChar();
      if (c == 'o') state = 18;
      else state = 10;
      break;
    case 18:
      c = nextChar();
      if (c == 's') state = 19;
      else state = 10;
      break;
    case 19:
      return new Token(Token::COS, getLexema());
    case 20:
      c = nextChar(); 
      if (c == '\0') state = 21;
      else state = 20;
      break;
    case 21:
      return new Token(Token::COMMENT, getComment());
    }
  }

}

Scanner::~Scanner() { }

char Scanner::nextChar() {
  int c = input[current];
  if (c != '\0') current++;
  return c;
}

void Scanner::rollBack() { // retract
  if (input[current] != '\0')
    current--;
}

void Scanner::startLexema() {
  first = current;
  return;
}

string Scanner::getLexema() {
  return input.substr(first,current-first);
}

string Scanner::getComment() {
  return input.substr(first + 1,current-first);
}





// ---------------------------------------------------

int main() {

  string s;
  fstream file("a.txt", ios::in);

  if (!file.is_open()) {
    cout << "Error opening file" << endl;
    exit(1);
  }

  int i = 1;
  string line;
  while (getline(file, line)) {
    s = line;

    cout << "Linea: " << i++ << ": " << s << endl;
    Scanner scanner(s.c_str());
    Token* tk = scanner.nextToken();

    while (tk->type != Token::END) {
      cout << "next token " << tk << endl;
      delete tk;
      tk =  scanner.nextToken();
    }
    cout << "last token " << tk << endl;
    delete tk;

    cout << endl;
  }

}



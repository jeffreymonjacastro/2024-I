#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

#include <unordered_map>

/*
  Scanner and Parser code inspired by code in Crafting Interpreters by Robert Nystrom
*/



class Token {
public:
	enum Type {
		LPAREN = 0, RPAREN, PLUS, MINUS, MULT, DIV, POW, NUM, FLOAT, ID, SIN, COS, LOG, PI, IF, ERR, END
	};
	static const char *token_names[17];
	Type type;
	string lexema;

	Token(Type);

	Token(Type, char c);

	Token(Type, const string source);
};

const char *Token::token_names[17] = {"LPAREN", "RPAREN", "PLUS", "MINUS", "MULT", "DIV", "POW", "NUM", "FLOAT", "ID",
									  "SIN", "COS", "LOG", "PI", "IF", "ERR", "END"};

Token::Token(Type type) : type(type) { lexema = ""; }

Token::Token(Type type, char c) : type(type) { lexema = c; }

Token::Token(Type type, const string source) : type(type) {
	lexema = source;
}

std::ostream &operator<<(std::ostream &outs, const Token &tok) {
	if (tok.lexema.empty())
		return outs << Token::token_names[tok.type];
	else
		return outs << Token::token_names[tok.type] << "(" << tok.lexema << ")";
}

std::ostream &operator<<(std::ostream &outs, const Token *tok) {
	return outs << *tok;
}


class Scanner {
public:
	Scanner(const char *in_s);

	Token *nextToken();

	~Scanner();

private:
	string input;
	int first, current;
	unordered_map<string, Token::Type> reserved;

	char nextChar();

	void rollBack();

	void startLexema();

	string getLexema();

	Token::Type checkReserved(string lexema);
};

Scanner::Scanner(const char *s) : input(s), first(0), current(0) {
	reserved["sin"] = Token::SIN;
	reserved["cos"] = Token::COS;
	reserved["log"] = Token::LOG;
	reserved["PI"] = Token::PI;
	reserved["if"] = Token::IF;
}

Token *Scanner::nextToken() {
	Token *token;
	char c;
	// consume whitespaces
	c = nextChar();

	while (c == ' ')
		c = nextChar();

	if (c == '\0') return new Token(Token::END);
	startLexema();

	if (isdigit(c) || c == '.') {
		c = nextChar();

		if (c == '.') {
			c = nextChar();

			while (isdigit(c))
				c = nextChar();

			rollBack();
			token = new Token(Token::FLOAT, getLexema());
		} else {
			while (isdigit(c))
				c = nextChar();
			rollBack();
			token = new Token(Token::NUM, getLexema());
		}


	} else if (isalpha(c)) {
		c = nextChar();
		while (isalpha(c))
			c = nextChar();
		rollBack();

		string lex = getLexema();

		Token::Type ttype = checkReserved(lex);

		if (ttype != Token::ERR)
			token = new Token(ttype);
		else
			token = new Token(Token::ID, getLexema());
	} else if (strchr("+-*/()", c)) {
		switch (c) {
			case '(':
				token = new Token(Token::LPAREN);
				break;
			case ')':
				token = new Token(Token::RPAREN);
				break;
			case '+':
				token = new Token(Token::PLUS);
				break;
			case '-':
				token = new Token(Token::MINUS);
				break;
			case '*':
				c = nextChar();
				if (c == '*') {
					token = new Token(Token::POW);
				} else {
					token = new Token(Token::MULT);
					rollBack();
				}

				break;
			case '/':
				token = new Token(Token::DIV);
				break;
			default:
				cout << "No deberia llegar aca" << endl;
				exit(0);
		}
	} else {
		token = new Token(Token::ERR, c);
	}
	return token;
}

Scanner::~Scanner() {}


/*

./sol.exe "1.2"

c = '1'
current = 1

c = '.'
current = 2



*/


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
	first = current - 1;
	return;
}

string Scanner::getLexema() {
	return input.substr(first, current - first);
}

Token::Type Scanner::checkReserved(string lexema) {
	// unordered_map<std::string,Token::Type>::const_iterator it = reserved.find (lexema);
	auto it = reserved.find(lexema);

	if (it == reserved.end())
		return Token::ERR;
	else
		return it->second;
}




// ---------------------------------------------------

int main(int argc, const char *argv[]) {

	if (argc != 2) {
		cout << "Incorrect number of arguments" << endl;
		exit(1);
	}

	Scanner scanner(argv[1]);
	Token *tk = scanner.nextToken();
	while (tk->type != Token::END) {
		cout << "next token " << tk << endl;
		delete tk;
		tk = scanner.nextToken();
	}
	cout << "last token " << tk << endl;
	delete tk;

}



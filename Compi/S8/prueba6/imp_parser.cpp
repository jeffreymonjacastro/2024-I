

#include "imp_parser.hh"


const char *Token::token_names[26] = {"LPAREN", "RPAREN", "PLUS", "MINUS",
									  "MULT", "DIV", "EXP", "LT", "LTEQ", "EQ",
									  "NUM", "IFEXP", "ID", "PRINT", "SEMICOLON", "COMMA", "ASSIGN",
									  "IF", "THEN", "ELSE", "ENDIF", "WHILE", "DO", "ENDWHILE"
									  "ERR", "END"};

Token::Token(Type type) : type(type) { lexema = ""; }

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


Scanner::Scanner(string s) : input(s), first(0), current(0) {
	reserved["print"] = Token::PRINT;
	reserved["if"] = Token::IF;
	reserved["then"] = Token::THEN;
	reserved["else"] = Token::ELSE;
	reserved["endif"] = Token::ENDIF;
	reserved["ifexp"] = Token::IFEXP;
	reserved["while"] = Token::WHILE;
	reserved["do"] = Token::DO;
	reserved["endwhile"] = Token::ENDWHILE;
}

Token *Scanner::nextToken() {
	Token *token;
	char c;
	// consume whitespaces
	c = nextChar();
	while (c == ' ' || c == '\t' || c == '\n') c = nextChar();
	if (c == '\0') return new Token(Token::END);
	startLexema();
	if (isdigit(c)) {
		c = nextChar();
		while (isdigit(c)) c = nextChar();
		rollBack();
		token = new Token(Token::NUM, getLexema());
	} else if (isalpha(c)) {
		c = nextChar();
		while (isalpha(c) || isdigit(c) || c == '_') c = nextChar();
		rollBack();
		string lex = getLexema();
		Token::Type ttype = checkReserved(lex);
		if (ttype != Token::ERR)
			token = new Token(ttype);
		else
			token = new Token(Token::ID, getLexema());
	} else if (strchr("()+-*/;=<,", c)) {
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
				if (c == '*') token = new Token(Token::EXP);
				else {
					rollBack();
					token = new Token(Token::MULT);
				}
				break;
			case '/':
				token = new Token(Token::DIV);
				break;
			case ';':
				token = new Token(Token::SEMICOLON);
				break;
			case ',':
				token = new Token(Token::COMMA);
				break;
			case '=':
				c = nextChar();
				if (c == '=') token = new Token(Token::EQ);
				else {
					rollBack();
					token = new Token(Token::ASSIGN);
				}
				break;
			case '<':
				c = nextChar();
				if (c == '=') token = new Token(Token::LTEQ);
				else {
					rollBack();
					token = new Token(Token::LT);
				}
				break;
			default:
				cout << "No deberia llegar aca" << endl;
		}
	} else {
		token = new Token(Token::ERR, getLexema());
	}
	return token;
}

Scanner::~Scanner() {}

char Scanner::nextChar() {
	int c = input[current];
	current++;
	return c;
}

void Scanner::rollBack() { // retract
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
	std::unordered_map<std::string, Token::Type>::const_iterator it = reserved.find(lexema);
	if (it == reserved.end())
		return Token::ERR;
	else
		return it->second;
}

/* ***************** Parser ********************* */


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
		Token *temp = current;
		if (previous) delete previous;
		current = scanner->nextToken();
		previous = temp;
		if (check(Token::ERR)) {
			cout << "Parse error, unrecognised character: " << current->lexema << endl;
			exit(0);
		}
		return true;
	}
	return false;
}

bool Parser::isAtEnd() {
	return (current->type == Token::END);
}

void Parser::parserError(string s) {
	cout << "Parsing error: " << s << endl;
	exit(0);
}

Parser::Parser(Scanner *sc) : scanner(sc) {
	previous = current = NULL;
	return;
};

Program *Parser::parse() {
	current = scanner->nextToken();
	if (check(Token::ERR)) {
		cout << "Error en scanner - caracter invalido" << endl;
		exit(0);
	}
	Program *p = parseProgram();
	if (current->type != Token::END) {
		cout << "Esperaba fin-de-input, se encontro " << current << endl;
		delete p;
		p = NULL;
	}

	if (current) delete current;
	return p;
}

Program *Parser::parseProgram() {
	return new Program(parseStatementList());
}

StatementList *Parser::parseStatementList() {
	StatementList *p = new StatementList();
	p->add(parseStatement());
	while (match(Token::SEMICOLON)) {
		p->add(parseStatement());
	}
	return p;
}

/*
  id = exp
  print(x)
 */
Stm *Parser::parseStatement() {
	Stm *s = NULL;
	Exp *e;
	StatementList *tsl, *fsl;
	if (match(Token::ID)) {
		string lex = previous->lexema;
		if (!match(Token::ASSIGN)) {
			cout << "Error: esperaba =" << endl;
			exit(0);
		}
		s = new AssignStatement(lex, parseExpression());
		//memoria_update(lex, v);
	} else if (match(Token::PRINT)) {
		if (!match(Token::LPAREN)) {
			cout << "Error: esperaba ( " << endl;
			exit(0);
		}
		e = parseExpression();
		if (!match(Token::RPAREN)) {
			cout << "Error: esperaba )" << endl;
			exit(0);
		}
		s = new PrintStatement(e);
	} else if (match(Token::IF)) {
		e = parseCExp();
		if (!match(Token::THEN))
			parserError("Esperaba 'then'");
		tsl = parseStatementList();
		fsl = NULL;
		if (match(Token::ELSE)) {
			fsl = parseStatementList();
		}
		if (!match(Token::ENDIF))
			parserError("Esperaba 'endif'");
		s = new IfStatement(e, tsl, fsl);
	} else if (match(Token::WHILE)) {
		e = parseCExp();
		cout << "Parse while" << endl;
		if (!match(Token::DO)){
			parserError("Esperaba DO");
		}
		cout << "Parse DO" << endl;
		tsl = parseStatementList();
		fsl = NULL;
		if (!match(Token::ENDWHILE)){
			parserError("Esperaba ENDWHILE");
		}
		cout << "Parse endlwhile" << endl;
		s = new WhileStatement(e, tsl);
	} else {
		cout << "No se encontro Statement" << endl;
		exit(0);
	}
	return s;
}

Exp *Parser::parseExpression() {
	return parseCExp();
}

Exp *Parser::parseCExp() {
	Exp *e, *rhs;
	e = parseAExp();
	if (match(Token::LT) || match(Token::LTEQ) || match(Token::EQ)) {
		Token::Type op = previous->type;
		BinaryOp binop = (op == Token::LT) ? LT : ((op == Token::LTEQ) ? LTEQ : EQ);
		rhs = parseAExp();
		e = new BinaryExp(e, rhs, binop);
	}
	return e;
}


Exp *Parser::parseAExp() {
	Exp *e, *rhs;
	e = parseTerm();
	while (match(Token::MINUS) || match(Token::PLUS)) {
		Token::Type op = previous->type;
		BinaryOp binop = (op == Token::MINUS) ? MINUS : PLUS;
		rhs = parseTerm();
		e = new BinaryExp(e, rhs, binop);
	}
	return e;
}

Exp *Parser::parseTerm() {
	Exp *e, *rhs;
	e = parseFExp();
	while (match(Token::MULT) || match(Token::DIV)) {
		Token::Type op = previous->type;
		BinaryOp binop = (op == Token::MULT) ? MULT : DIV;
		rhs = parseFExp();
		e = new BinaryExp(e, rhs, binop);
	}
	return e;
}

Exp *Parser::parseFExp() {
	Exp *lhs, *rhs;
	lhs = parseFactor();
	if (match(Token::EXP)) {
		return new BinaryExp(lhs, parseFExp(), EXP);
	}
	return lhs;
}

Exp *Parser::parseFactor() {
	Exp *e1, *e2, *e3;

	if (match(Token::NUM)) {
		return new NumberExp(stoi(previous->lexema));
	}
	if (match(Token::ID)) {
		return new IdExp(previous->lexema);
	}
	if (match(Token::LPAREN)) {
		Exp *e = parseExpression();
		if (!match(Token::RPAREN)) {
			cout << "Expecting right parenthesis" << endl;
			exit(0);
		}
		// return e; is fine too
		return new ParenthExp(e);
	}
	if (match(Token::IFEXP)) {
		cout << "Parsea IFEXP" << endl;
		if (!match(Token::LPAREN)) {
			parserError("Se esperaba paréntesis izq");
		}
		cout << "Voy a parsear la primera expresion" << endl;
		e1 = parseExpression();
		if (!match(Token::COMMA)) {
			parserError("Se esperaba una coma");
		}
		cout << "Voy a parsear la segunda expresion" << endl;
		e2 = parseExpression();
		if (!match(Token::COMMA)) {
			parserError("Se esperaba una coma");
		}
		cout << "Voy a parsear la tercera expresion" << endl;
		e3 = parseExpression();
		if (!match(Token::RPAREN)){
			parserError("Se esperaba paréntesis der");
		}
		cout << "Voy a parsear parentesis der" << endl;

		return new CondExp(e1, e2, e3);
	}
	cout << "Couldn't find match for token: " << current << endl;
	exit(0);
}









// ---------------------------------------------------




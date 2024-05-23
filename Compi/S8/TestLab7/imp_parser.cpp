

#include "imp_parser.hh"


const char *Token::token_names[27] = {"LPAREN", "RPAREN", "PLUS", "MINUS",
									  "MULT", "DIV", "EXP",
									  "NUM", "ID", "PRINT", "SEMICOLON", "ASSIGN", "ERR", "END", "LT", "LTEQ", "EQ",
									  "IF", "ELSE", "THEN", "ENDIF", "AND", "OR", "NOT",
									  "WHILE", "ENDL", "FOR"
};

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
	reserved["else"] = Token::ELSE;
	reserved["then"] = Token::THEN;
	reserved["endif"] = Token::ENDIF;
	reserved["and"] = Token::AND;
	reserved["or"] = Token::OR;
	reserved["not"] = Token::NOT;
	reserved["while"] = Token::WHILE;
	reserved["endl"] = Token::ENDL;
	reserved["for"] = Token::FOR;

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
	} else if (strchr("()+-*/;<=", c)) {
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
	cout << "TERMINO EL PROGRAMA " << current << endl;
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
	// p->add(parseStatement());
	//cout<<current<<"  CON ESTO DENTRO DE ST LIST"<<endl;
	//cout<<"PARSEANDO POR ALGO "<<endl;
	while (true) {
		// cout<<current<<"   DENTRO"<<endl;
		p->add(parseStatement());
		match(Token::SEMICOLON);
		if (current->type == Token::END or current->type == Token::ELSE or current->type == Token::ENDIF or
			current->type == Token::ENDL)
			break;
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
		cout << "CURRENT SALIR DE  ->" << current << endl;
		if (!match(Token::RPAREN)) {
			cout << "Error: esperaba )" << endl;
			exit(0);
		}
		s = new PrintStatement(e);
	} else if (match(Token::IF)) {
		StatementList *p1 = new StatementList();
		StatementList *p2 = new StatementList();

		cout << "ENTRE AL IF :3" << endl;
		e = parseExpression();
		if (match(Token::THEN)) {
			cout << "VOY A PARSEAR LA LISTA THEN" << endl;
			p1 = parseStatementList();
			cout << "TERMINE DE PARSEAR LA LISTA THEN" << endl;

		}
		if (match(Token::ELSE)) {
			cout << "ENCONTRE UN ELSE" << endl;
			p2 = parseStatementList();
		} else p2 = nullptr;

		cout << previous << "BEFORE DISASTER" << endl;
		cout << current << "-->IS ALL PARSED?" << endl;
		if (!match(Token::ENDIF)) {
			cout << "Expresion has no endif " << endl;
			exit(0);
		}

		s = new IfStatement(e, p1, p2);

	} else if (match(Token::WHILE)) {
		cout << "WHILE INSIDE " << endl;
		StatementList *p1 = new StatementList();
		e = parseExpression();
		cout << "CONDITION WHILE  PARSED" << endl;
		if (match(Token::THEN))
			p1 = parseStatementList();
		if (!match(Token::ENDL)) {
			cout << "Expresion has no endif " << endl;
			exit(0);
		}
		cout << "WHILE PARSED RETURN THIS " << endl;

		s = new WhileStament(e, p1);

	} else if (match(Token::FOR)) {
		Stm *init, *iterator;
		StatementList *l1;
		if (match(Token::LPAREN)) {
			init = parseStatement();
			match(Token::SEMICOLON);
			e = parseExpression();
			match(Token::SEMICOLON);
			iterator = parseStatement();
		}

		if (!match(Token::RPAREN)) {
			cout << "Expresion has no rparent " << endl;
			exit(0);
		}

		if (match(Token::THEN))
			l1 = parseStatementList();

		if (!match(Token::ENDL)) {
			cout << "Expresion has no rparent " << endl;
			exit(0);
		}

		s = new ForStatement(init, e, iterator, l1);

	} else {
		cout << "No se encontro Statement" << endl;
		exit(0);
	}
	return s;
}


Exp *Parser::parseExpression() {
	Exp *e, *rhs;
	e = parseNotexpression();
	while (match(Token::AND) or match(Token::OR)) {
		Token::Type op = previous->type;
		BinaryOp binop = (op == Token::OR) ? OR : AND;
		rhs = parseNotexpression();
		cout << "current" << current << endl;
		e = new BinaryExp(e, rhs, binop);
	}

	return e;
}

Exp *Parser::parseNotexpression() {
	Exp *negation, *e;
	if (match(Token::NOT)) {
		cout << current << " dentro del not ??" << endl;
		BinaryOp binop = NOT;
		e = parseCExpression();
		cout << "CURRENT AFTER DARK " << current << endl;
		e = new BinaryExp(nullptr, e, binop);
	} else e = parseCExpression();

	return e;
}


Exp *Parser::parseCExpression() {

	Exp *lhs, *rhs;
	cout << "VOY A PARSEAR UNA COMPARACION antes " << current << endl;
	lhs = parseAexpression();
	cout << "LHS next" << current << endl;
	if (match(Token::LT) or match(Token::LTEQ) or match(Token::EQ)) {
		Token::Type op = previous->type;
		cout << previous->type << endl;
		BinaryOp binop;
		switch (op) {
			case Token::EQ:
				binop = EQ;
				break;
			case Token::LT:
				binop = LT;
				break;
			case Token::LTEQ:
				binop = LTEQ;
				break;
		}
		rhs = parseAexpression();
		cout << "RHS next " << current << endl;
		lhs = new BinaryExp(lhs, rhs, binop);

	}

	return lhs;
}


Exp *Parser::parseAexpression() {
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
	cout << "Couldn't find match for token: " << current << endl;
	exit(0);
}









// ---------------------------------------------------




#include "prueba4.hh"
#include <cmath>


string Exp::binopToString(BinaryOp op) {
	switch (op) {
		case PLUS:
			return "+";
		case MINUS:
			return "-";
		case MULT:
			return "*";
		case DIV:
			return "/";
		case EXP:
			return "**";
	}
	return "";
}


// Constructors
BinaryExp::BinaryExp(Exp *l, Exp *r, BinaryOp op) : left(l), right(r), op(op) {}

NumberExp::NumberExp(int v) : value(v) {}

IdExp::IdExp(string id) : id(id) {}

ParenthExp::ParenthExp(Exp *e) : e(e) {}

TrigExp::TrigExp(Exp *e, TrigonometryOp op): e(e), op(op) {}

Exp::~Exp() {}

BinaryExp::~BinaryExp() {
	delete left;
	delete right;
}

NumberExp::~NumberExp() {}

IdExp::~IdExp() {}

ParenthExp::~ParenthExp() { delete e; }

TrigExp::~TrigExp() { delete e; }


// print
void BinaryExp::print() {
	left->print();
	cout << ' ' << Exp::binopToString(this->op) << ' ';
	right->print();
}

void NumberExp::print() {
	cout << value;
}

void IdExp::print() {
	cout << id;
}

void ParenthExp::print() {
	cout << '(';
	e->print();
	cout << ')';
}

void TrigExp::print(){
	cout << (op == SIN ? "sin(" : "cos(");
	e->print();
	cout << ')';
}

// eval
double BinaryExp::eval() {
	double v1 = left->eval();
	double v2 = right->eval();
	double result = 0;
	switch (this->op) {
		case PLUS:
			result = v1 + v2;
			break;
		case MINUS:
			result = v1 - v2;
			break;
		case MULT:
			result = v1 * v2;
			break;
		case DIV:
			result = v1 / v2;
			break;
		case EXP:
			result = 1;
			while (v2 > 0) {
				result *= v1;
				v2--;
			}
			break;
	}
	return result;
}

double NumberExp::eval() {
	return value;
}

double IdExp::eval() {
	if (Program::memoria_check(id))
		return Program::memoria_lookup(id);
	else {
		cout << "Variable indefinida: " << id << endl;
		exit(0);
	}
	return 0;
}

double ParenthExp::eval() {
	return e->eval();
}

double TrigExp::eval() {
	double v = e->eval();
	double result;

	switch(this->op) {
		case SIN:
			result = sin(v * M_PI / 180);
			break;
		case COS:
			result = cos(v * M_PI / 180);
	}

	cout << result << endl;
	return result;
}


AssignStatement::AssignStatement(string id, Exp *e) : id(id), rhs(e) {}

PrintStatement::PrintStatement(Exp *e) : e(e) {}

Stm::~Stm() {}

AssignStatement::~AssignStatement() { delete rhs; }

PrintStatement::~PrintStatement() { delete e; }

Program::~Program() {
	// loop
}

void AssignStatement::print() {
	cout << id << " = ";
	rhs->print();
}

void AssignStatement::execute() {
	int v = rhs->eval();
	Program::memoria_update(id, v);
}

void PrintStatement::print() {
	cout << "print(";
	e->print();
	cout << ")";
}

void PrintStatement::execute() {
	double v = e->eval();
	cout << v << endl;
}

Program::Program() : slist() {}

void Program::add(Stm *s) { slist.push_back(s); }


void Program::print() {
	cout << "{" << endl;
	list<Stm *>::iterator it;
	for (it = slist.begin(); it != slist.end(); ++it) {
		(*it)->print();
		cout << ";" << endl;
	}
	cout << "}" << endl;
}

void Program::execute() {
	list<Stm *>::iterator it;
	for (it = slist.begin(); it != slist.end(); ++it) {
		(*it)->execute();
	}
}

unordered_map<string, int> Program::memoria;

void Program::memoria_update(string x, int v) {
	Program::memoria[x] = v;
}

bool Program::memoria_check(string x) {
	std::unordered_map<std::string, int>::const_iterator it = Program::memoria.find(x);
	if (it == Program::memoria.end())
		return false;
	else
		return true;
}

int Program::memoria_lookup(string x) {
	std::unordered_map<std::string, int>::const_iterator it = Program::memoria.find(x);
	if (it == Program::memoria.end())
		return 0;
	else
		return it->second;
}







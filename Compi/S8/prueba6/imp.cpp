#include "imp.hh"
#include "imp_visitor.hh"

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
		case LT:
			return "<";
		case LTEQ:
			return "<=";
		case EQ:
			return "==";
	}
	return "";
}


// Constructors
BinaryExp::BinaryExp(Exp *l, Exp *r, BinaryOp op) : left(l), right(r), op(op) {}

NumberExp::NumberExp(int v) : value(v) {}

IdExp::IdExp(string id) : id(id) {}

ParenthExp::ParenthExp(Exp *e) : e(e) {}

CondExp::CondExp(Exp *e1, Exp *e2, Exp *e3): e1(e1), e2(e2), e3(e3) {}

Exp::~Exp() {}

BinaryExp::~BinaryExp() {
	delete left;
	delete right;
}

NumberExp::~NumberExp() {}

IdExp::~IdExp() {}

ParenthExp::~ParenthExp() { delete e; }

CondExp::~CondExp() {
	delete e1;
	delete e2;
	delete e3;
}

int BinaryExp::accept(ImpVisitor *v) {
	return v->visit(this);
}

int NumberExp::accept(ImpVisitor *v) {
	return v->visit(this);
}

int IdExp::accept(ImpVisitor *v) {
	return v->visit(this);
}

int ParenthExp::accept(ImpVisitor *v) {
	return v->visit(this);
}

int CondExp::accept(ImpVisitor *v) {
	return v->visit(this);
}

AssignStatement::AssignStatement(string id, Exp *e) : id(id), rhs(e) {}

PrintStatement::PrintStatement(Exp *e) : e(e) {}

IfStatement::IfStatement(Exp *c, StatementList *tsl, StatementList *fsl) : cond(c), tsl(tsl), fsl(fsl) {}

WhileStatement::WhileStatement(Exp *c, StatementList *sl) {}

StatementList::StatementList() : slist() {}

Program::Program(StatementList *sl) : slist(sl) {}

Stm::~Stm() {}

AssignStatement::~AssignStatement() { delete rhs; }

PrintStatement::~PrintStatement() { delete e; }

IfStatement::~IfStatement() {
	delete fsl;
	delete tsl;
	delete cond;
}

WhileStatement::~WhileStatement(){
	delete cond;
	delete sl;
}

StatementList::~StatementList() {}

Program::~Program() {
	// loop
}

void AssignStatement::accept(ImpVisitor *v) {
	return v->visit(this);
}

void PrintStatement::accept(ImpVisitor *v) {
	return v->visit(this);
}

void IfStatement::accept(ImpVisitor *v) {
	return v->visit(this);
}

void WhileStatement::accept(ImpVisitor *v) {
	return v->visit(this);
}

void StatementList::add(Stm *s) { slist.push_back(s); }

void StatementList::accept(ImpVisitor *v) {
	return v->visit(this);
}

void Program::accept(ImpVisitor *v) {
	return v->visit(this);
}










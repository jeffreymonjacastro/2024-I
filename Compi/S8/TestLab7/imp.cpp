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
        case EQ:
            return "==";
        case LTEQ:
            return "<=";
        case AND:
            return "and";
        case OR:
            return "or";
        case NOT:
            return "not";
    }
    return "";
}


// Constructors
BinaryExp::BinaryExp(Exp *l, Exp *r, BinaryOp op) : left(l), right(r), op(op) {}

NumberExp::NumberExp(int v) : value(v) {}

IdExp::IdExp(string id) : id(id) {}

ParenthExp::ParenthExp(Exp *e) : e(e) {}

Exp::~Exp() {}

BinaryExp::~BinaryExp() {
    delete left;
    delete right;
}

NumberExp::~NumberExp() {}

IdExp::~IdExp() {}

ParenthExp::~ParenthExp() { delete e; }

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

AssignStatement::AssignStatement(string id, Exp *e) : id(id), rhs(e) {}

PrintStatement::PrintStatement(Exp *e) : e(e) {}

StatementList::StatementList() : slist() {}

Program::Program(StatementList *sl) : slist(sl) {}

// IF
IfStatement::IfStatement(Exp *condition_, StatementList *then_list_, StatementList *else_list_) : condition(condition_),
                                                                                                  then_list(then_list_),
                                                                                                  else_list(
                                                                                                          else_list_) {}

//WHILE
WhileStament::WhileStament(Exp *contdition_, StatementList *list_) : condition(contdition_), while_list(list_) {}

//FOR
ForStatement::ForStatement(Stm * initializer_, Exp * cond_, Stm * iterator_, StatementList * list_) :
initializer(initializer_),contidition(cond_),iterator(iterator_),for_list(list_){}


Stm::~Stm() {}

AssignStatement::~AssignStatement() { delete rhs; }

PrintStatement::~PrintStatement() { delete e; }

StatementList::~StatementList() {}

ForStatement::~ForStatement() noexcept {

    //loop
}


WhileStament::~WhileStament() {
    //loop;
}

IfStatement::~IfStatement() {
    //loop
}

Program::~Program() {
    // loop
}


void ForStatement::accept(ImpVisitor *v) {
    return v->visit(this);
}


void WhileStament::accept(ImpVisitor *v) {
    return v->visit(this);
}

void IfStatement::accept(ImpVisitor *v) {
    return v->visit(this);
}

void AssignStatement::accept(ImpVisitor *v) {
    return v->visit(this);
}

void PrintStatement::accept(ImpVisitor *v) {
    return v->visit(this);
}

void StatementList::add(Stm *s) { slist.push_back(s); }

void StatementList::accept(ImpVisitor *v) {
    return v->visit(this);
}

void Program::accept(ImpVisitor *v) {
    return v->visit(this);
}










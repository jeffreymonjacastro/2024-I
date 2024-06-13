#include "imp_typechecker.hh"

ImpTypeChecker::ImpTypeChecker() {

}

void ImpTypeChecker::typecheck(Program *p) {
	env.clear();
	p->accept(this);
	return;
}

void ImpTypeChecker::visit(Program *p) {
	p->body->accept(this);
	return;
}

void ImpTypeChecker::visit(Body *b) {
	env.add_level();
	b->var_decs->accept(this);
	b->slist->accept(this);
	env.remove_level();
	return;
}

void ImpTypeChecker::visit(VarDecList *decs) {
	list<VarDec *>::iterator it;
	for (it = decs->vdlist.begin(); it != decs->vdlist.end(); ++it) {
		(*it)->accept(this);
	}
	return;
}

void ImpTypeChecker::visit(VarDec *vd) {
	list<string>::iterator it;
	ImpType tt = ImpValue::get_basic_type(vd->type);
	if (tt == NOTYPE) {
		cout << "Tipo invalido: " << vd->type << endl;
		exit(0);
	}
	for (it = vd->vars.begin(); it != vd->vars.end(); ++it) {
		env.add_var(*it, tt);
	}
	return;
}


void ImpTypeChecker::visit(StatementList *s) {
	list<Stm *>::iterator it;
	for (it = s->slist.begin(); it != s->slist.end(); ++it) {
		(*it)->accept(this);
	}
	return;
}

void ImpTypeChecker::visit(AssignStatement *s) {
	ImpType type = s->rhs->accept(this);
	// typecheck
	if (!env.check(s->id)) {
		cout << "Variable " << s->id << " undefined" << endl;
		exit(0);
	}

	ImpType lhs = env.lookup(s->id);

	if (lhs != type) {
		cout << "Type mismatch in assignment" << endl;
		exit(0);
	}

	return;
}

void ImpTypeChecker::visit(PrintStatement *s) {
	s->e->accept(this);
	return;
}

void ImpTypeChecker::visit(IfStatement *s) {
	ImpType v = s->cond->accept(this);
	if (v != TBOOL) {
		cout << "Type error en If: esperaba bool en condicional" << endl;
		exit(0);
	}

	s->tbody->accept(this);
	if (s->fbody != NULL)
		s->fbody->accept(this);
	return;
}

void ImpTypeChecker::visit(WhileStatement *s) {
	ImpType tcond = s->cond->accept(this);
	if (tcond != TBOOL) {
		cout << "Type error en While: esperaba bool en condicional" << endl;
		exit(0);
	}
	s->body->accept(this);
	return;
}

ImpType ImpTypeChecker::visit(BinaryExp *e) {
	ImpType t1 = e->left->accept(this);
	ImpType t2 = e->right->accept(this);
	ImpType result;

	if (t1 != t2) {
		cout << "Los tipos de los operandos no coinciden" << endl;
		exit(0);
	}

	switch (e->op) {
		case PLUS: result = TINT; break;
		case MINUS: result = TINT; break;
		case MULT: result = TINT; break;
		case DIV: result = TINT; break;
		case EXP: result = TINT; break;
		case LT: result = TBOOL; break;
		case LTEQ: result = TBOOL; break;
		case EQ: result = TBOOL; break;
		case AND: result = TBOOL; break;
		case OR: result = TBOOL; break;
	}
	return result;
}

ImpType ImpTypeChecker::visit(NumberExp *e) {
	ImpType t = TINT;
	return t;
}

ImpType ImpTypeChecker::visit(IdExp *e) {
	ImpType t = env.lookup(e->id);
	return t;
}

ImpType ImpTypeChecker::visit(ParenthExp *ep) {
	return ep->e->accept(this);
}

ImpType ImpTypeChecker::visit(CondExp *e) {
	ImpType btype = e->cond->accept(this);

	if (btype != TBOOL) {
		cout << "Tipo invalido en condicional" << endl;
		exit(0);
	}

	ImpType ttype = e->etrue->accept(this);
	ImpType ftype = e->efalse->accept(this);

	return NOTYPE;
}

ImpType ImpTypeChecker::visit(BoolExp *e) {
	ImpType t = TBOOL;
	return t;
}

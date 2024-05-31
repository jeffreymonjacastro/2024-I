#include "imp_printer.hh"

void ImpPrinter::print(Program *p) {
	cout << "Program : ";
	p->accept(this);
	return;
}

void ImpPrinter::visit(Program *p) {
	cout << "{" << endl;
	p->body->accept(this);
	cout << "}" << endl;
	return;
}

int ImpPrinter::visit(Body *b) {
	b->var_decs->accept(this);
	b->slist->accept(this);
	return 0;
}

int ImpPrinter::visit(VarDecList *v) {
	list<VarDec *>::iterator it;
	for (it = v->vdlist.begin(); it != v->vdlist.end(); ++it) {
		(*it)->accept(this);
	}
	return 0;
}

int ImpPrinter::visit(VarDec *v) {
	if (!v->vars.empty()) {
		cout << "var " << v->type << " ";
		list<string>::iterator it;
		for (it = v->vars.begin(); it != v->vars.end(); ++it) {
			if (it == v->vars.begin())
				cout << (*it);
			else
				cout << "," << (*it);
		}
		cout << ";" << endl;
	}
	return 0;
}


void ImpPrinter::visit(StatementList *s) {
	list<Stm *>::iterator it;
	for (it = s->slist.begin(); it != s->slist.end(); ++it) {
		(*it)->accept(this);
		cout << ";" << endl;
	}
	return;
}

void ImpPrinter::visit(AssignStatement *s) {
	cout << s->id << " = ";
	s->rhs->accept(this);
	return;
}

void ImpPrinter::visit(PrintStatement *s) {
	cout << "print(";
	s->e->accept(this);
	cout << ")";
	return;
}

void ImpPrinter::visit(IfStatement *s) {
	cout << "if (";
	s->cond->accept(this);
	cout << ") then" << endl;
	s->tsl->accept(this);
	if (s->fsl != NULL) {
		cout << "else" << endl;
		s->fsl->accept(this);
	}
	cout << "endif";
	return;
}

void ImpPrinter::visit(WhileStatement *s) {
	cout << "while (";
	s->cond->accept(this);
	cout << ") do" << endl;;
	s->sl->accept(this);
	cout << "endwhile";
	return;
}

int ImpPrinter::visit(BinaryExp *e) {
	e->left->accept(this);
	cout << ' ' << Exp::binopToString(e->op) << ' ';
	e->right->accept(this);
	return 0;
}

int ImpPrinter::visit(NumberExp *e) {
	cout << e->value;
	return 0;
}

int ImpPrinter::visit(IdExp *e) {
	cout << e->id;
	return 0;
}

int ImpPrinter::visit(ParenthExp *ep) {
	cout << '(';
	ep->e->accept(this);
	cout << ')';
	return 0;
}

int ImpPrinter::visit(CondExp *e) {
	cout << "ifexp(";
	e->cond->accept(this);
	cout << ",";
	e->etrue->accept(this);
	cout << ",";
	e->efalse->accept(this);
	cout << ')';
	return 0;
}

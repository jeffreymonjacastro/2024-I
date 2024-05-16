#include "imp_interpreter.hh"

string ImpInterpreter::interpret(Program *p) {
	p->accept(this);
	return "";
}

string ImpInterpreter::visit(Program *p) {
	list<Stm *>::iterator it;
	for (it = p->slist.begin(); it != p->slist.end(); ++it) {
		(*it)->accept(this);
	}
	return "";
}

string ImpInterpreter::visit(AssignStatement *s) {
	string v = s->rhs->accept(this);
	env.update(s->id, v);
	return "";
}

string ImpInterpreter::visit(PrintStatement *s) {
	string v = s->e->accept(this);
	cout << v << endl;
	return "";
}

string ImpInterpreter::visit(BinaryExp *e) {
	string v1 = e->left->accept(this);
	string v2 = e->right->accept(this);
	string result;

	// elimina las comillas simples de cada cadena
	if (v1[0] == '\'' && v1[v1.size() - 1] == '\'')
		v1 = v1.substr(1, v1.size() - 2);
	if (v2[0] == '\'' && v2[v2.size() - 1] == '\'')
		v2 = v2.substr(1, v2.size() - 2);

	result = '\'' + v1 + v2 + '\'';

	cout << "Bytes: " << v1.size() + v2.size() << endl;

//	switch (e->op) {
//		case PLUS:
//			result = v1 + v2;
//			break;
//		case MINUS:
//			result = v1 - v2;
//			break;
//		case MULT:
//			result = v1 * v2;
//			break;
//		case DIV:
//			result = v1 / v2;
//			break;
//		case EXP:
//			result = 1;
//			while (v2 > 0) {
//				result *= v1;
//				v2--;
//			}
//			break;
//	}
	return result;
}

//int ImpInterpreter::visit(NumberExp* e) {
//  return e->value;
//}

string ImpInterpreter::visit(Cadena *e) {
	return e->cadena;
}


string ImpInterpreter::visit(IdExp *e) {
	if (env.check(e->id))
		return env.lookup(e->id);
	else {
		cout << "Variable indefinida: " << e->id << endl;
		exit(0);
	}
}

string ImpInterpreter::visit(ParenthExp *ep) {
	return ep->e->accept(this);
}



#ifndef INC_2024_I_IMP_MEMORY_HH
#define INC_2024_I_IMP_MEMORY_HH

#include "imp_visitor.hh"

class ImpMemory: public ImpVisitor {
public:
	string visit(Program* p){
		int res;
		list<Stm *>::iterator it;
		for (it = p->slist.begin(); it != p->slist.end(); ++it) {
			(*it)->accept(this);
			res += 1;
		}
		return to_string(res);
	}

	string visit(AssignStatement *);

	string visit(PrintStatement *);

	string visit(Cadena *e);

	string visit(BinaryExp *e);

	string visit(IdExp *e);

	string visit(ParenthExp *e);
};


#endif //INC_2024_I_IMP_MEMORY_HH

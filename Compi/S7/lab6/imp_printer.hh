#ifndef IMP_PRINTER
#define IMP_PRINTER

#include "imp.hh"
#include "imp_visitor.hh"

class ImpPrinter : public ImpVisitor {
public:
	void print(Program *);

	string visit(Program *);

	string visit(AssignStatement *);

	string visit(PrintStatement *);

	string visit(Cadena *e);

	string visit(BinaryExp *e);

//	int visit(NumberExp *e);

	string visit(IdExp *e);

	string visit(ParenthExp *e);
};


#endif


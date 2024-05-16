#ifndef IMP_VISITOR
#define IMP_VISITOR

#include "imp.hh"

class ImpVisitor {
public:
	virtual string visit(Program *e) = 0;

	virtual string visit(AssignStatement *e) = 0;

	virtual string visit(PrintStatement *e) = 0;

	virtual string visit(BinaryExp *e) = 0;

//	virtual int visit(NumberExp *e) = 0;

	virtual string visit(IdExp *e) = 0;

	virtual string visit(Cadena *e) = 0;

	virtual string visit(ParenthExp *e) = 0;
};


#endif

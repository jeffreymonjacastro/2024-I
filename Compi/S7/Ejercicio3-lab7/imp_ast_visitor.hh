#ifndef IMP_AST_VISITOR
#define IMP_AST_VISITOR

#include "imp.hh"

class ImpASTVisitor {
public:
	virtual int visit(Program *e) = 0;

	virtual int visit(AssignStatement *e) = 0;

	virtual int visit(PrintStatement *e) = 0;

	virtual int visit(BinaryExp *e) = 0;

	virtual int visit(NumberExp *e) = 0;

	virtual int visit(IdExp *e) = 0;

	virtual int visit(ParenthExp *e) = 0;
};


#endif

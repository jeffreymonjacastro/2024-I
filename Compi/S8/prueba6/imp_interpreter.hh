#ifndef IMP_INTERPRETER
#define IMP_INTERPRETER

#include "imp.hh"
#include "imp_visitor.hh"
#include "environment.hh"

class ImpInterpreter : public ImpVisitor {
private:
	Environment env;
public:
	int interpret(Program *);

	void visit(Program *);

	void visit(StatementList *);

	void visit(AssignStatement *);

	void visit(PrintStatement *);

	void visit(IfStatement *);

	void visit(WhileStatement *);

	int visit(BinaryExp *e);

	int visit(NumberExp *e);

	int visit(IdExp *e);

	int visit(ParenthExp *e);

	int visit(CondExp *e);
};


#endif


#ifndef IMP_INTERPRETER
#define IMP_INTERPRETER

#include <unordered_map>
#include "imp.hh"
#include "imp_visitor.hh"
#include "environment.hh"

using namespace std;

class ImpInterpreter : public ImpVisitor {
private:
  Environment env;
public:
	string interpret(Program*);
    string visit(Program*);
	string visit(AssignStatement*);
	string visit(PrintStatement*);
    string visit(Cadena* e);
	string visit(BinaryExp* e);
//    int visit(NumberExp* e);
	string visit(IdExp* e);
	string visit(ParenthExp* e);
};


#endif


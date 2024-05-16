#ifndef IMP_AST
#define IMP_AST

#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>

#include <list>

using namespace std;

class ImpVisitor;

enum BinaryOp {
	PLUS, MINUS, MULT, DIV, EXP
};


class Exp {
public:
	virtual string accept(ImpVisitor *v) = 0;

	static string binopToString(BinaryOp op);

	virtual ~Exp() = 0;
};

class BinaryExp : public Exp {
public:
	Exp *left, *right;
	BinaryOp op;

	BinaryExp(Exp *l, Exp *r, BinaryOp op);

	string accept(ImpVisitor *v);

	~BinaryExp();
};

//class NumberExp : public Exp {
//public:
//	int value;
//
//	NumberExp(int v);
//
//	int accept(ImpVisitor *v);
//
//	~NumberExp();
//};

class Cadena : public Exp {
public:
	string cadena;

	Cadena(string);

	string accept(ImpVisitor *v);

	~Cadena();
};

class IdExp : public Exp {
public:
	string id;

	IdExp(string id);

	string accept(ImpVisitor *v);

	~IdExp();
};

class ParenthExp : public Exp {
public:
	Exp *e;

	ParenthExp(Exp *e);

	string accept(ImpVisitor *v);

	~ParenthExp();
};

class Stm {
public:
	virtual string accept(ImpVisitor *v) = 0;
//	virtual int accept(ImpMemory *v) = 0

	virtual ~Stm() = 0;
};


class AssignStatement : public Stm {
public:
	string id;
	Exp *rhs;

	AssignStatement(string id, Exp *e);

	string accept(ImpVisitor *v);

	~AssignStatement();
};

class PrintStatement : public Stm {
public:
	Exp *e;

	PrintStatement(Exp *e);

	string accept(ImpVisitor *v);

	~PrintStatement();
};


class Program {
public:
	list<Stm *> slist;

	Program();

	void add(Stm *s);

	string accept(ImpVisitor *v);

	~Program();
};


#endif


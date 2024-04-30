#include <sstream>
#include <iostream>
#include <iostream>

#include "exp.hh"
#include "exp_parser.hh"

int main(int argc, const char *argv[]) {

	bool useparser = true;
	Exp *exp1, *exp2, *exp3;

	if (useparser) {

		if (argc != 2) {
			cout << "Incorrect number of arguments" << endl;
			exit(1);
		}
		Scanner scanner(argv[1]);
		Parser parser(&scanner);
		exp1 = parser.parse();  // el parser construye la aexp

	} else {  // contruyendo ASTs a mano

		exp1 = new BinaryExp(new NumberExp(3), new NumberExp(2), EXP);
		exp2 = new BinaryExp(new NumberExp(5), exp1, PLUS);
		exp3 = new BinaryExp(exp2, new NumberExp(2), DIV);

	}

	if (exp1 != NULL) {
		cout << "expr: ";
		exp1->print();

		cout << endl;

		cout << "eval: ";
		cout << exp1->eval() << endl;

		delete exp1;

	}

}

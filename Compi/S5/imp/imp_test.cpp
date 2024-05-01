#include <sstream>
#include <iostream>
#include <iostream>

#include "imp.hh"
#include "imp_parser.hh"

int main(int argc, const char *argv[]) {

	bool useparser = true;
	Program *program;

	if (useparser) {

		if (argc != 2) {
			cout << "Incorrect number of arguments" << endl;
			exit(1);
		}

		Scanner scanner(argv[1]);
		Parser parser(&scanner);
		program = parser.parse();  // el parser construye el AST de Program

	} else {
		program = new Program();
		Exp *e1 = new BinaryExp(new NumberExp(8), new NumberExp(9), PLUS);
		Exp *e2 = new BinaryExp(new NumberExp(4), new NumberExp(3), MULT);
		Stm *s1 = new AssignStatement("x", e1);
		Stm *s2 = new AssignStatement("y", e2);
		Stm *s3 = new PrintStatement(new BinaryExp(new IdExp("x"), new IdExp("y"), PLUS));
		program->add(s1);
		program->add(s2);

	}

	cout << "program: " << endl;
	program->print();
	cout << endl;

	cout << "execute: " << endl;
	program->execute();

	delete program;


}

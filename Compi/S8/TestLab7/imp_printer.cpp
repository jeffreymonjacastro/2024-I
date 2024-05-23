#include "imp_printer.hh"

void ImpPrinter::print(Program* p) {
  cout << "Program : ";
  p->accept(this);
  return;
}

void ImpPrinter::visit(Program* p) {
  p->slist->accept(this);
  return;
}

void ImpPrinter::visit(StatementList* s) {
  cout << "{" << endl;
  list<Stm*>::iterator it;
  for (it = s->slist.begin(); it != s->slist.end(); ++it) {
    (*it)->accept(this);
    cout << ";" << endl;
  }
  cout << "}" << endl;
  return;
}

void ImpPrinter::visit(AssignStatement* s) {
  cout << s->id << " = ";
  s->rhs->accept(this);
  return;
}

void ImpPrinter::visit(PrintStatement* s) {
  cout << "print(";
  s->e->accept(this);
  cout << ")";
  return;
}


void ImpPrinter::visit(ForStatement* for_st) {
    cout<<"for ( ";
    for_st->initializer->accept(this);
    cout<<";";
    for_st->contidition->accept(this);
    cout<<";";
    for_st->iterator->accept(this);
    cout<<"; )";
    for_st->for_list->accept(this);
    cout<<"ENDL";
}


void ImpPrinter::visit(WhileStament * while_st) {
    cout<<"WHILE ";
    while_st->condition->accept(this);
    cout<<"THEN"<<endl;
    while_st->while_list->accept(this);
    cout<<"ENDL";

}

void ImpPrinter::visit(IfStatement * if_st) {
    cout <<"IF " ;
    if_st->condition->accept(this);
    cout<<" THEN :";
    if_st->then_list->accept(this) ;


    if(if_st->else_list!= nullptr){
        cout<<"ELSE :";
        if_st->else_list->accept(this);
    }

    cout<<"ENDIF" <<endl;

}



int ImpPrinter::visit(BinaryExp* e) {
   if(e->left!= nullptr) e->left->accept(this);
  cout << ' ' << Exp::binopToString(e->op) << ' ';
  e->right->accept(this);
  return 0;
}

int ImpPrinter::visit(NumberExp* e) {
  cout << e->value;
  return 0;
}

int ImpPrinter::visit(IdExp* e) {
  cout << e->id;
  return 0;
}

int ImpPrinter::visit(ParenthExp* ep) {
  cout << '(';
  ep->e->accept(this);
  cout << ')';
  return 0;
}

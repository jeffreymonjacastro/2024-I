#include "imp_interpreter.hh"


int ImpInterpreter::interpret(Program* p) {
  p->accept(this);
  return 0;
}

void ImpInterpreter::visit(Program* p) {
  p->slist->accept(this);
  return;
}

void ImpInterpreter::visit(StatementList* s) {
  list<Stm*>::iterator it;
  for (it = s->slist.begin(); it != s->slist.end(); ++it) {
    (*it)->accept(this);
  }
  return;
}

void ImpInterpreter::visit(AssignStatement* s) {
  int v = s->rhs->accept(this);
  env.update(s->id, v);  
  return;
}

void ImpInterpreter::visit(PrintStatement* s) {
  int v = s->e->accept(this);
  cout << v << endl;
  return;
}

int ImpInterpreter::visit(BinaryExp* e) {
    int v1;
    if(e->left!= nullptr){
        v1 = e->left->accept(this);
    }
  int v2 = e->right->accept(this);

  int result = 0;
  switch(e->op) {
  case PLUS: result = v1+v2; break;
  case MINUS: result = v1-v2; break;
  case MULT: result = v1 * v2; break;
  case DIV: result = v1 / v2; break;
  case EXP:
    result = 1;
    while (v2 > 0) { result *= v1; v2--; }
    break;
    case LT : result =int(v1<v2);
          break;
      case LTEQ: result = int (v1<=v2);
          break;
      case EQ: result = int (v1==v2);
          break;
      case AND: result =  v1 and v2 ;
          break;
      case OR: result = v1 or v2 ;
          break;
      case NOT: result = not v2;
  }
  return result;
}

int ImpInterpreter::visit(NumberExp* e) {
  return e->value;
}

int ImpInterpreter::visit(IdExp* e) {
  if (env.check(e->id))
    return env.lookup(e->id);
  else {
    cout << "Variable indefinida: " << e->id << endl;
    exit(0);
  }
  return 0;
}

int ImpInterpreter::visit(ParenthExp* ep) {
  return ep->e->accept(this);
}

void ImpInterpreter::visit(IfStatement * if_st) {

    if(if_st->condition->accept(this))
        if_st->then_list->accept(this);
    else {
        if(if_st->else_list!= nullptr)
            if_st->else_list->accept(this);
    }


}

void ImpInterpreter::visit(WhileStament * while_st) {
    while(while_st->condition->accept(this))
        while_st->while_list->accept(this);
}


void ImpInterpreter::visit(ForStatement * for_st) {

    for_st->initializer->accept(this);

    while (for_st->contidition->accept(this))
    {
        for_st->for_list->accept(this);
        for_st->iterator->accept(this);
    }

}


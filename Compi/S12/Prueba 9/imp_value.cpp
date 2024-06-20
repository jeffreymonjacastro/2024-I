#include "imp_value.hh"

ImpValue::ImpValue():type(NOTYPE) { }

ImpType ImpValue::get_basic_type(string s) {
  ImpType tt;
  if (s.compare("int")==0) tt = TINT;
  else if (s.compare("bool")==0) tt = TBOOL;
  else if (s.compare("float") == 0) tt = TFLOAT;
  else tt = NOTYPE; 
  return tt;
}

void ImpValue::set_default_value(ImpType tt) {
  type = tt;
  if (tt == TINT) {
    int_value = 0;
  } else if (tt == TBOOL) {
    bool_value = true;
  } else if (tt == TFLOAT){
    float_value = 0.;
  }
  return;
}

std::ostream& operator << ( std::ostream& outs, const ImpValue & v )
{
  if (v.type == TINT)
    outs << v.int_value;
  else if (v.type == TBOOL) {
    if (v.bool_value)
      outs << "true";
    else
      outs << "false";
  } else if (v.type == TFLOAT){
    outs << v.float_value;
  } else {
    outs << "NOTYPE";
  }
  return outs;
}



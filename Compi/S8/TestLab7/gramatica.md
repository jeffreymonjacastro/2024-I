## Gramática:

Corto
```
Program        ::= StatementList
StatementList  ::= Stm ("," Stm)*
Stm            ::= AssignStm
                   | PrintStm
                   | IfStm
                   | WhileStm
                   | ForStm 
Exp            ::= NExp [("and" | "or") NExp]
NExp           ::= ("not")? CExp
CExp           ::= AExp [("<" | "<=" | "==") AExp]
AExp           ::= Term [("+" | "-") Term]
Term           ::= FExp [("*" | "/") FExp]
FExp           ::= Factor [("**") FExp]
Factor         ::= num | id | Exp
```

```
Program        ::= StatementList
StatementList  ::= Stm ("," Stm)*
Stm            ::= id "=" Exp 
                   | "print" "(" CExp ")"
                   | "if" CExp "then" StatementList ["else" StatementList] "endif"
                   | "while" "(" CExp ")" "then" StatementList "endl"
                   | "for" "(" Stm ";" CExp ";" Stm ")" "then" StatementList "endl" 
Exp            ::= NExp [("and" | "or") NExp]
NExp           ::= ("not")? CExp
CExp           ::= AExp [("<" | "<=" | "==") AExp]
AExp           ::= Term [("+" | "-") Term]
Term           ::= FExp [("*" | "/") FExp]
FExp           ::= Factor [("**") FExp]
Factor         ::= num | id | Exp
```



## Gramática:

```
Program        ::= StatementList
StatementList  ::= Stm ("," Stm)*
Stm            ::= id "=" CExp | 
                   "print" "(" CExp ")" |
                   "if" CExp "then" StatementList ["else" StatementList] "endif"
CExp           ::= Exp [("<" | "<=" | "==") Exp]
Exp            ::= Term [("+" | "-") Term]
Term           ::= FExp [("*" | "/") FExp]
FExp           ::= Factor [("**") FExp]
Factor         ::= num | id | Exp
```



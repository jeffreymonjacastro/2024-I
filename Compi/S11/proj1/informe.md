# Projecto 1 - (Compiladores CS3025)

## Resumen
En este proyecto se implementaron mejoras al compilador del lenguaje IMP-DEC que se desarrolló en el curso de Compiladores CS3025. Las mejoras implementadas fueron las siguientes:

1. **Typechecker y Codegen**: Se implementó un `typechecker` y un `codegen` para la gramática IMP-DEC.

2. **Generación de Código I**: Se modificó el `Scanner` y `Parser` para que soporte la inclusión de comentarios en el código fuente. 

3. **Sentencia Do While**: Se implementó la sentencia `do while` en el lenguaje IMP-DEC.


## Tabla de Contenidos

- [Projecto 1 - (Compiladores CS3025)](#projecto-1---compiladores-cs3025)
  - [Resumen](#resumen)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Gramática del lenguaje IMP-DEC](#gramática-del-lenguaje-imp-dec)
  - [1. Typechecker y Codegen](#1-typechecker-y-codegen)
    - [1.1. Typechecker](#11-typechecker)
    - [1.2. Codegen](#12-codegen)
    - [Ejemplo de uso](#ejemplo-de-uso)
  - [2. Generación de Código I](#2-generación-de-código-i)
  - [3. Sentencia Do While](#3-sentencia-do-while)
  - [Autores](#autores)
  - [Referencias](#referencias)

## Gramática del lenguaje IMP-DEC
La gramática que se utilizó en el proyecto es la siguiente:

```js
Program         ::= Body
Body            ::= VarDecList StatementList 
VarDecList      ::= (VarDec)*
VarDec          ::= "var" Type VarList ";" ("//" Comment)?
Type            ::= id
VarList         ::= id ("," id)*
StatementList   ::= (Stm)+ 
Stm             ::= id "=" Exp ";" ("//" Comment)?           |
                    "print" "(" Exp ")" ";" ("//" Comment)?  |
                    "if" Exp "then" Body "else" Body "endif" |
                    "while" Exp "do" Body "endwhile"         |
                    "do" Body "while" Exp "enddo"            |
Exp             ::= BExp
BExp            ::= CEXP (("and" | "or") BExp)?
CEXP            ::= AExp (("==" | "<" | "<=" ) AExp)?
AExp            ::= Term (("+" | "-") Term)*
Term            ::= FExp (("*" | "/") FExp)*
FExp            ::= Factor ("**" FExp)?
Factor          ::= id                                                       | 
                    num                                                      | 
                    true                                                     |
                    false                                                    |
                    "(" Exp ")"                                              | 
                    "ifexp" "(" Exp "," Exp "," Exp ")"
```

## 1. Typechecker y Codegen

### 1.1. Typechecker
El Typechecker es un visitor que recorre el AST parseado y verifica que las variables utilizadas en el programa estén declaradas y que los tipos de las variables sean correctos. En caso de que haya un error, el Typechecker lanza una excepción con un mensaje de error. 

Los archivos modificados para implementar el Typechecker son:
+ `type_visitor.hh`: Interfaz **TypeVisitor** que funcionará como visitor para el Typechecker.
+ `imp_typecheker.hh`: Clase **ImpTypeChecker** que implementa la interfaz **TypeVisitor**. Este a su vez tiene un Environment de tipo **ImpType** que almacenará las variables (key) y sus tipos (value).
+ `imp_typecheker.cpp`: Definición de la clase **ImpTypeChecker**. Aquí se implementan los métodos de visitor para cada regla de la gramática.

#### Implementación del Typechecker

```cpp
cout << "Hello World" << endl;

 
```


### 1.2. Codegen

El Codegen es un visitor que recorre el AST parseado y genera el código intermedio en formato de tres direcciones. El código intermedio generado es almacenado en un vector de strings.


### Ejemplo de uso


> **⚠️ Reporte: ¿Cómo se calculó la memoria necesaria para las variables globales?**  \
Respuesta


## 2. Generación de Código I


> **⚠️ Reporte: ¿Qué cambios se hicieron al scanner y/o parser para lograr la inclusión de comentarios?**  \
Respuesta


## 3. Sentencia Do While 


> **⚠️ Reporte: Indicar el cambio a la gramática y los puntos donde se hicieron cambios al código. Además, proveer las definiciones de tcheck y codegen usadas**  \
Respuesta


## Autores

| **Benjamin Soto** | **Fabrizzio Vilchez** | **Jeffrey Monja** |
|:------------:|:------------:|:------------:|
| ![Benjamin Soto](https://avatars.githubusercontent.com/u/104233590?v=4) | ![Fabrizzio Vilchez](https://avatars.githubusercontent.com/u/115495332?v=4) | ![Jeffrey Monja](https://avatars.githubusercontent.com/u/104637993?v=4) |
| [https://github.com/SotoBenjamin](https://github.com/SotoBenjamin) | [https://github.com/Fabrizzio20k](https://github.com/Fabrizzio20k) | [https://github.com/jeffreymonjacastro](https://github.com/jeffreymonjacastro) |


## Referencias 

- W. Appel. (2002) Modern compiler implementation in Java. 2.a edición. CambridgeUniversity Press.
- Kenneth C. Louden. (2004) Compiler Construction: Principles and Practice.Thomson.

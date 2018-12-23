/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
#include "tokenscanner.h"

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */
enum statement{REMSTA,LETSTA, PRINTSTA,INPUTSTA,QUITSTA,IFSTA,GOTOSTA,ENDSTA};

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: exe = stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 *
 * the returned value of the function means the function execution situation.
 */


    virtual int execute_(EvalState & state) = 0;
    virtual statement getType() = 0;
    string line;//it is the original string of the statement.
};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */
class RemSta: public Statement{
/*
 * This statement is used for comments.
 */
    public:
    RemSta() = default;
    RemSta(string inp)
    {
      line = inp;
    }
    virtual int execute_(EvalState & state);
    virtual statement getType();
    ~RemSta(){};
};

class LetSta: public Statement{
/*
 * This statement is BASIC’s assignment statement.
 */
public:
    LetSta()= default;
    LetSta(string inp);
    virtual int execute_(EvalState & state);
    virtual statement getType(){ return LETSTA; };
    ~LetSta(){delete exp;};

private:
    string var,op;
    Expression *exp;

};

class InputSta: public Statement{
/*
 * This statement print a prompt consisting of the string " ? "
 * and then to read in a value to be stored in the variable.
 */
public:
    InputSta() = default;
    InputSta(string inp);
    virtual int execute_(EvalState & state);
    virtual statement getType();
    ~ InputSta(){};
private:
    string var;
    int num;
};

class PrintSta: public Statement{
/*
 * This statement print the value of the expression
 * on the console and then print a newline character.
 */
public:
    PrintSta()= default;
    PrintSta(string inp);
    virtual int execute_(EvalState & state);
    virtual statement getType(){return PRINTSTA;};
    ~PrintSta(){delete exp;}
private:
    Expression *exp;
};



class Gotosta: public Statement{
/*
 * This class transfers control unconditionally to line n in the program.
 * If line n does not exist,
 * BASIC interpreter should generate an error message informing the user of that fact.
 */
public:
    Gotosta()
    {
        /*empty*/
    }
    Gotosta(string inp);
    virtual int execute_(EvalState & state);
    virtual statement getType(){ return  GOTOSTA;};
    ~Gotosta(){};
private:

    int tolinenum;
};


class Ifsta: public Statement{
    /*
  * This statement performs a conditional transfer of control.
  * On encountering such a statement,
  * the BASIC interpreter begins by evaluating condition,
  * which in the minimal version of BASIC consists of two arithmetic expressions
  * joined by one of the operators <, >, or =.
  * If the result of the comparison is true,
  * control passes to line n,
  * just as in the GOTO statement;
  * if not, the program continues with the next line in sequence.
  */
public:

    Ifsta()
    {
        /*empty*/
    }
    Ifsta(string inp);
    virtual int execute_(EvalState & state);
    virtual statement getType(){return IFSTA;};
private:
    string exps1,exps2;
    Expression *exp1,*exp2;
    int toline;
    string op;
};
class Quitsta:public Statement{
public:
    Quitsta(string inp){line = inp;};
    virtual int execute_(EvalState & state){ return 0 ;};
    virtual statement getType(){return QUITSTA;};
};
class Endsta:public Statement{
public:
    Endsta(string inp){line = inp;};
    virtual int execute_(EvalState & state){ return 0 ;};
    virtual statement getType(){return ENDSTA;};
};

#endif

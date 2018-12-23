/*
 * File: program.h
 * ---------------
 * This interface exports a Program class for storing a BASIC
 * program.
 */

#ifndef _program_h
#define _program_h

#include <string>
#include "evalstate.h"
#include "statement.h"

using namespace std;
struct Line{
    string str="";
    Statement *parsedsta = NULL;
    Line(string st = "",Statement *sta = NULL){
        str = st;
        parsedsta = sta;
    }

    /*Line(Line &z){
        str = z.str;
        parsedsta = z.parsedsta;
    }*/
    ~Line(){}
};

/*
 * This class stores the lines in a BASIC program.  Each line
 * in the program is stored in order according to its line number.
 * Moreover, each line in the program is associated with two
 * components:
 *
 * 1. The source line, which is the complete line (including the
 *    line number) that was entered by the user.
 *
 * 2. The parsed representation of that statement, which is a
 *    pointer to a Statement.
 */

class Program {

public:

/*
 * Constructor: Program
 * Usage: Program program;
 * -----------------------
 * Constructs an empty BASIC program.
 */

    Program();

/*
 * Destructor: ~Program
 * Usage: usually implicit
 * -----------------------
 * Frees any heap storage associated with the program.
 */

    ~Program();

/*
 * Method: clear
 * Usage: program.clear();
 * -----------------------
 * Removes all lines from the program.
 */

    void clear();

/*
 * Method: addSourceLine
 * Usage: program.addSourceLine(lineNumber, line);
 * -----------------------------------------------
 * Adds a source line to the program with the specified line number.
 * If that line already exists, the text of the line replaces
 * the text of any existing line and the parsed representation
 * (if any) is deleted.  If the line is new, it is added to the
 * program in the correct sequence.
 */

    void addSourceLine(int lineNumber,Line line_);
/*
 * Method: removeSourceLine
 * Usage: program.removeSourceLine(lineNumber);
 * --------------------------------------------
 * Removes the line with the specified number from the program,
 * freeing the memory associated with any parsed representation.
 * If no such line exists, this method simply returns without
 * performing any action.
 */

    void removeSourceLine(int lineNumber);

/*
 * Method: getSourceLine
 * Usage: string line = program.getSourceLine(lineNumber);
 * -------------------------------------------------------
 * Returns the program line with the specified line number.
 * If no such line exists, this method returns the empty string.
 */

    std::string getSourceLine(int lineNumber);

/*
 * Method: setParsedStatement
 * Usage: program.setParsedStatement(lineNumber, stmt);
 * ----------------------------------------------------
 * Adds the parsed representation of the statement to the statement
 * at the specified line number.  If no such line exists, this
 * method raises an error.  If a previous parsed representation
 * exists, the memory for that statement is reclaimed.
 */

    void setParsedStatement(int lineNumber, Statement *stmt);

/*
 * Method: getParsedStatement
 * Usage: Statement *stmt = program.getParsedStatement(lineNumber);
 * ----------------------------------------------------------------
 * Retrieves the parsed representation of the statement at the
 * specified line number.  If no value has been set, this method
 * returns NULL.
 */

    Statement *getParsedStatement(int lineNumber);

/*
 * Method: getFirstLineNumber
 * Usage: int lineNumber = program.getFirstLineNumber();
 * -----------------------------------------------------
 * Returns the line number of the first line in the program.
 * If the program has no lines, this method returns -1.
 */

    int getFirstLineNumber();

/*
 * Method: getNextLineNumber
 * Usage: int nextLine = program.getNextLineNumber(lineNumber);
 * ------------------------------------------------------------
 * Returns the line number of the first line in the program whose
 * number is larger than the specified one, which must already exist
 * in the program.  If no more lines remain, this method returns -1.
 */

    int getNextLineNumber(int lineNumber);

/*
 * This function starts program execution beginning at the lowest-numbered line
 */
    void run(EvalState &state);

/*
 * This function lists the steps in the program in numerical sequence.
 */
    void list();

/*
 * This function deletes all program and variables.
 */
    void clear(EvalState &state);

/*
 * This function exits from the BASIC interpreter by calling exit(0).
 */
    void quit() {
        exit(0);
    }

/*
 * This function provides a simple help message describing your interpreter.
 */
    void help();

    void flagtofalse(){
        flag = false;
    }

private:
    bool flag = true;
    map <int, Line> linemap;
};

#endif

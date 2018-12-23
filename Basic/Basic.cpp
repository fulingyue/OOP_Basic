/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: Fu Lingyue]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "statement.h"
#include "evalstate.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   while (true) {
      try
      {
         processLine(getLine(), program, state);

      }
      catch (ErrorException & ex)
      {
         cerr << "Error: " << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */
void DIRECTexecute(string identifier,string line,EvalState & state,TokenScanner &scan){
    Statement *sta = NULL;
    if(identifier == "LET")
    {
        sta = new LetSta(line);
        int exe = sta -> execute_(state);
        if(exe > 0){
            if(exe == 1e9){
                cout << "VARIABLE NOT DEFINED" << endl;
                return;
            }
            return;
        }
        else return;
    }
    if(identifier == "PRINT")
    {
        sta = new PrintSta(line);
        int exe = sta -> execute_(state);
        if( exe > 0) {
            if (exe == 1e9) {
                cout << "VARIABLE NOT DEFINED" << endl;
                return;
            }
            return;
        }
        else return;
    }
    if(identifier == "INPUT")
    {
        sta = new InputSta(line);
        int exe = sta->execute_(state);
        while(exe < 0){
            cout << "INVALID NUMBER" << endl;
            exe = sta->execute_(state);
        }
        return;
    }
}

void processLine(string line, Program & program, EvalState & state) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   string inp = scanner.nextToken();
   if(inp == "LET" || inp == "PRINT" || inp =="INPUT")
   {
      DIRECTexecute(inp,line,state,scanner);
       return;
   }

   if(scanner.getTokenType(inp) == NUMBER)
   {

       int linenum = -1;
       stringstream stream;
       stream << inp;
       stream >> linenum;
       //cout << linenum;
       /*if(stream.fail() || stream.eof() || linenum < 0) {
           cout << "SYNTAX ERROR1" << endl;
           program.flagtofalse();
       }*/
       if(!scanner.hasMoreTokens())
       {
           program.removeSourceLine(linenum);
           return;
       }
       else
       {
           Statement *sta = NULL;
           inp = scanner.nextToken();
           if(inp == "REM"){
               sta = new RemSta(line);
           }
           else if(inp == "LET"){
               sta = new LetSta(line);
           }
           else if(inp == "INPUT"){
               sta = new InputSta(line);
           }
           else if(inp == "PRINT"){
               sta = new PrintSta(line);
           }
           else if(inp == "END"){
               sta = new Endsta(line);
           }
           else if(inp == "GOTO"){
               sta = new Gotosta(line);
           }
           else if(inp == "IF"){
               sta = new Ifsta(line);
           }
           else if(inp == "QUIT"){
               sta = new Quitsta(line);
           }
           else{
               cout << "SYNTAX ERROR2" << endl;
               delete sta;
               program.flagtofalse();
               return;
           }
           Line line_(sta->line,sta);
           program.addSourceLine(linenum,line_);
           return;
       }
   }
   else
   {
       if(inp == "RUN")
            program.run(state);
       else if(inp == "LIST")
           program.list();
       else if(inp == "CLEAR")
           program.clear(state);
       else if(inp == "QUIT")
           program.quit();
       else if(inp == "HELP")
           program.help();
       else {
            cout << "SYNTAX ERROR3" << endl;
            program.flagtofalse();
       }
       return;
   }
}

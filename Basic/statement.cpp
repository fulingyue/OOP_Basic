/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include <sstream>
#include "statement.h"
#include "parser.h"
#include "../StanfordCPPLib/strlib.h"
#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/tokenscanner.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement(){
   /* Empty */
}

Statement::~Statement(){
   /* Empty */
}

int RemSta::execute_(EvalState &state)
{
    return 1;
}
statement RemSta::getType(){
    return REMSTA;
}

LetSta::LetSta(string inp) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    line = inp;
    scanner.setInput(line);
    if(scanner.getTokenType(scanner.nextToken()) == NUMBER){
        string identifier = scanner.nextToken();
    }
    var = scanner.nextToken();
    op = scanner.nextToken();
    exp = parseExp(scanner);

}

int LetSta::execute_(EvalState & state){
    if(op != "=") {
        cout << "SYNTAX ERROR5" << endl;
        return -1;
    }
    else{
        if(var == "LET"){
            cout << "SYNTAX ERROR" << endl;
            return -1;
        }
        int val = exp->eval(state);
        if(val == 1e9) return 1e9;
        else {
            state.setValue(var,val);
            return 1;
        }
    }
}

InputSta::InputSta(string inp){
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    line = inp;
    scanner.setInput(line);
    if(scanner.getTokenType(scanner.nextToken()) == NUMBER){
        string identifier = scanner.nextToken();
    }
    var = scanner.nextToken();
}

int InputSta::execute_(EvalState & state){
    string inp;
    cout << " ? " ;
    getline(cin,inp);
    //if(!checkerror(inp))return -1;
    istringstream is(inp);
    is >> num;
    if (is.fail() || !is.eof()) return -1;
    else {
        state.setValue(var, num);
        return 1;
    }

}
statement InputSta::getType(){
    return INPUTSTA;
}

PrintSta::PrintSta(string inp) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    line = inp;
    scanner.setInput(line);
    string nxt = scanner.nextToken();
    if(scanner.getTokenType(nxt) == NUMBER){
        nxt = scanner.nextToken();
    }
    if( nxt != "PRINT")
        cout << "SYNTAX ERROR" << endl;
    TokenScanner scanexp;
    scanexp.ignoreWhitespace();
    while(scanner.hasMoreTokens()){
        scanexp.saveToken(scanner.nextToken());
    }
    TokenScanner scanexp2;
    scanexp2.ignoreWhitespace();
    while(scanexp.hasMoreTokens()){
        scanexp2.saveToken(scanexp.nextToken());
    }
    exp = parseExp(scanexp2);
}

int PrintSta::execute_(EvalState & state){

    int out = exp->eval(state);
    if( out == -1e9)
        cout << "DIVIDE BY ZERO" << endl;
    else if (out == 1e9) return (int)1e9;
    else {
        cout << out << endl;
        return 1;
    }
}

Gotosta::Gotosta(string inp){
    line = inp;
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.setInput(line);
    if(scanner.getTokenType(scanner.nextToken()) != NUMBER)
        cout << "SYNTAX ERROR10" << endl;
    else{
        string nxt = scanner.nextToken();
        if(!scanner.hasMoreTokens())
            cout << "SYNTAX ERROR6" << endl;
        else {
            nxt = scanner.nextToken();
            stringstream is;
            is << nxt;
            is >> tolinenum;
        }
    }
}
int Gotosta::execute_(EvalState &state) {
    return tolinenum;
}


Ifsta::Ifsta(string inp){
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    line = inp;
    scanner.setInput(line);
    if(scanner.getTokenType(scanner.nextToken()) != NUMBER)
        cout << "SYNTAX ERROR7" <<endl;
    else if(scanner.nextToken() != "IF")
        cout << "SYNTAX ERROR7" <<endl;
    else if(!scanner.hasMoreTokens())
        cout << "SYNTAX ERROR7" <<endl;

    TokenScanner scan1;
    scan1.ignoreWhitespace();
    string nxt = scanner.nextToken();
    while(scanner.hasMoreTokens() && nxt != "<"
    && nxt != ">" && nxt != "="){
        exps1 += nxt + " ";
        nxt = scanner.nextToken();
    }
    scan1.setInput(exps1);
    op = nxt;
    exp1 = parseExp(scan1);

    nxt = scanner.nextToken();
    TokenScanner scan2;
    scan2.ignoreWhitespace();
    while(scanner.hasMoreTokens()&& nxt != "THEN"){
       exps2 += nxt + " ";
       nxt =scanner.nextToken();
    }
    scan2.setInput(exps2);
    exp2 = parseExp(scan2);
    istringstream is(scanner.nextToken());
    is >> toline;
}
int Ifsta::execute_(EvalState & state){
    bool bo;
    if(op == ">") {
        if(exp1->eval(state) > exp2->eval(state)) bo = 1;
        else bo = 0;
    }
    else if(op == "="){
        int left = exp1->eval(state);
        int right = exp2->eval(state);
        if(left == right) bo = 1;
        else bo = 0;
    }
    else if(op == "<"){
        if(exp1->eval(state) < exp2->eval(state)) bo = 1;
        else bo = 0;
    }
    else {
        cout << "SYNTAX ERROR8" <<endl;
        return -1;
    }
    if(bo == 0){
        return 0;
    }
    else{
        return toline;
    }
}



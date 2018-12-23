/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "map.h"
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program() {
    /*empty*/
}

Program::~Program() {
    clear();
}

void Program::clear() {
    map<int,Line>::iterator it;
    for(it = linemap.begin();it != linemap.end();it++){
        delete it ->second.parsedsta;
    }
    linemap.clear();
}

void Program::addSourceLine(int lineNumber,Line line_) {
    linemap[lineNumber] = line_;
}

void Program::removeSourceLine(int lineNumber) {
    if(!linemap.count(lineNumber))return;
    else {
        linemap.erase(lineNumber);
        return;
    }
}

string Program::getSourceLine(int lineNumber) {
   if(!linemap.count(lineNumber))
       return "";
   else{
       return linemap[lineNumber].str;
   }
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    if(!linemap.count(lineNumber)){
        cout << "SYNTAX ERROR9" << endl;
    }
    else{
        linemap[lineNumber].parsedsta = stmt;
    }
}

Statement *Program::getParsedStatement(int lineNumber) {
    if(!linemap.count(lineNumber)) {
        return NULL;
    }
    else{
        return linemap[lineNumber].parsedsta;
    }
}

int Program::getFirstLineNumber() {
    if(linemap.empty()) return -1;
    map<int,Line> :: iterator it;
    it = linemap.begin();
   return it->first;
}

int Program::getNextLineNumber(int lineNumber) {
    map<int,Line> :: iterator it;
    it = linemap.find(lineNumber);
    it++;
    if(it == linemap.end()) {
        return -1;
    }
    else {
        return it->first;
    }
}

void Program::run(EvalState &state)
{
    int linenumnow = getFirstLineNumber();

    while(linenumnow > 0 && flag) {
        Statement *sta = linemap[linenumnow].parsedsta;
        if (sta->getType() == REMSTA || sta->getType() == LETSTA ||
             sta->getType() == PRINTSTA
            ) {
            int exe = sta->execute_(state);
            if( exe > 0) {
                if(exe == 1e9){
                    cout << "VARIABLE NOT DEFINED" << endl;
                    break;
                }
                else {
                    linenumnow = getNextLineNumber(linenumnow);
                }
            }
            else quit();
        }
        else if(sta->getType() == INPUTSTA){
            int exe = sta->execute_(state);
            while(exe < 0){
                exe = sta->execute_(state);
                cout << "INVALID NUMBER" << endl;
            }
            linenumnow = getNextLineNumber(linenumnow);
        }
        else if(sta->getType() == QUITSTA)
            quit();
        else if(sta->getType()== ENDSTA)
            break;
        else if (sta->getType() == IFSTA) {
            int nxt = sta->execute_(state);
            if ( nxt == 0)
                linenumnow = getNextLineNumber(linenumnow);
            else if(nxt < 0) {
                cout << "SYNTAX ERROR 7" << endl;
                break;
            }
            else linenumnow = nxt;
        }
        else if (sta->getType() == GOTOSTA){
            linenumnow = sta->execute_(state);
            if(!linemap.count(linenumnow)) {
                cout << "LINE NUMBER ERROR" << endl;
                break;
            }
        }
    }
    return;
}

void Program::list(){
    int linenumbernow = getFirstLineNumber();
    while(linenumbernow > 0){
        cout << getSourceLine(linenumbernow) << endl;
        linenumbernow = getNextLineNumber(linenumbernow);
    }
    return;
}

void Program::clear(EvalState &state){
    linemap.clear();
    state.clear();
}
void Program::help() {
    cout << "YOU CAN ONLY RELY ON YOURSELF" << endl;
}

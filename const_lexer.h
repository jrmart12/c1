#include "lexer.h"
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
using std::istringstream;
using std::string;
using std::cout;
using std::endl;
using std::fstream;
class ConstLexer {

    private:
        std::istream &in;
        int line;
        string text;
    public:
        ConstLexer(std::istream &in): in(in) { }
        const char* toString(Token tk);
        int getLine() { return line; }
        string getText() { return text; }
        void reportError(char ch) {
            cout << "error at line " <<line+1<< " with " << ch << endl;
        }
        char getNextChar() {
            char ch = in.get();
            if (ch == '\n') line++;
            return ch;
        }

        void ungetChar(char ch) {
            if (ch == '\n') line--;
            in.unget();
        }
        Token getNextToken();
        //Proto.nextToken: Token ConstLexer::getNextToken()
        //Proto.toString: const char* ConstLexer::toString(Token tk)
        //fa2lexer --hdr lexer.h --src lexer.cpp ./fa/start.jff
        
};
#ifndef __LEXER_H__
#define __LEXER_H__

enum class StateId {
    Start_q0,
    Start_q10,
    Start_q2,
    Start_q3,
    Start_q5,
    Start_q8,
};

enum Token {
    Octal,
    Decimal,
    Hex,
    Eof,
    Binary,
};
#endif
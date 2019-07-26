Token ConstLexer::getNextToken() {
    StateId state = StateId::Start_q0;
    int ch = getNextChar();

    while (true) {
        switch (state) {
            // Start
            case StateId::Start_q0:
                if ((ch == '\n') || (ch == ' ') || (ch == '\t')) {
                    state = StateId::Start_q0;
                    ch = getNextChar();
                } else if (ch == EOF) {
                    return Eof;
                } else {
                    state = StateId::Start_q10;
                    text="";
                }
                break;
            case StateId::Start_q10:
                if ((ch >= '2') && (ch <= '9')) {
                    text += ch;
                    state = StateId::Start_q5;
                    ch = getNextChar();
                } else if ((ch >= 'a') && (ch <= 'f')) {
                    text += ch;
                    state = StateId::Start_q3;
                    ch = getNextChar();
                } else if ((ch >= '0') && (ch <= '1')) {
                    text += ch;
                    state = StateId::Start_q2;
                    ch = getNextChar();
                } else {
                    reportError(ch);
                    ch = getNextChar();
                    state = StateId::Start_q0;
                }
                break;
            case StateId::Start_q2:
                if ((ch >= '2') && (ch <= '8')) {
                    text += ch;
                    state = StateId::Start_q5;
                    ch = getNextChar();
                } else if (ch == 'b') {
                    text += ch;
                    return Binary;
                } else if ((ch >= '0') && (ch <= '1')) {
                    text += ch;
                    state = StateId::Start_q2;
                    ch = getNextChar();
                } else {
                    reportError(ch);
                    ch = getNextChar();
                    state = StateId::Start_q0;
                }
                break;
            case StateId::Start_q3:
                if ((ch >= 'a') && (ch <= 'f')) {
                    text += ch;
                    state = StateId::Start_q3;
                    ch = getNextChar();
                } else if (ch == 'h') {
                    text += ch;
                    return Hex;
                } else {
                    reportError(ch);
                    ch = getNextChar();
                    state = StateId::Start_q0;
                }
                break;
            case StateId::Start_q5:
                if ((ch >= '1') && (ch <= '8')) {
                    text += ch;
                    state = StateId::Start_q5;
                    ch = getNextChar();
                } else if (isdigit(ch)) {
                    text += ch;
                    state = StateId::Start_q8;
                    ch = getNextChar();
                } else if (ch == 'o') {
                    text += ch;
                    return Octal;
                } else {
                    ungetChar(ch);
                    return Decimal;
                }
                break;
            case StateId::Start_q8:
                if (isdigit(ch)) {
                    text += ch;
                    state = StateId::Start_q8;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Decimal;
                }
                break;
        }
    }
}
const char* ConstLexer::toString(Token tk) {
    switch (tk) {
        case Octal: return "Octal";
        case Decimal: return "Decimal";
        case Hex: return "Hex";
        case Eof: return "Eof";
        case Binary: return "Binary";
        default: return "Unknown";
    }
}
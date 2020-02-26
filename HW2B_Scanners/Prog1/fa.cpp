#include<iostream>
#include<fstream>
#include<string>

using namespace std;

#define IDENT_TYPE_START_MSG "Trying the IDENT_TYPE machine..."
#define CURRENT_STATE_PREFIX_MSG "current state: "
#define CURRENT_CHAR_PREFIX_MSG "character: "
#define STUCK_IN_STATE_PREFIX_MSG "I am stuck in state "

enum TOKEN_TYPE {
    ERROR, MY_TOKEN, IDENT, REAL, INT
};

//------------------------------------------------
// CS421 File fa.cpp for HW2B DFA->Scanner Function
// Your name: **Anthony Machado
//------------------------------------------------

// ** Change this to fit the HW2B specification - look for **
// ** Must have the same types of tracing couts as mytoken.
// ** Must complete the ** comments with RE

// ---------- DFAs follow -------------------------

// MY_TOKEN DFA done by Rika Sensei has a sample
// This FA is for a b^+
bool mytoken(string s) {
    int state = 0;
    int charpos = 0;

    cout << "Trying the mytoken machine..." << endl;

    while (s[charpos] != '\0') {
        cout << "current state: " << state << endl;
        cout << "character: " << s[charpos] << endl;

        if (state == 0 && s[charpos] == 'a')
            state = 1;
        else if (state == 1 && s[charpos] == 'b')
            state = 2;
        else if (state == 2 && s[charpos] == 'b')
            state = 2;
        else {
            cout << STUCK_IN_STATE_PREFIX_MSG << state << endl;
            return (false);
        }
        charpos++;
    }//end of while

    // where did I end up????
    if (state == 2) return (true);  // end in a final state
    else return (false);
}// end of mytoken


// IDENT DFA
// This FA is for RE: ** a(b | 2 | _ )^*
bool ident_token(string const &word) {
    unsigned int state = 0;
    unsigned int const acceptedState = 1;

    cout << IDENT_TYPE_START_MSG << endl;

    for (char const &character : word) {
        cout << CURRENT_STATE_PREFIX_MSG << state << endl;
        cout << CURRENT_CHAR_PREFIX_MSG << character << endl;

        // condition of transitions for the regular expression
        if (state == 0 && character == 'a') {
            state = acceptedState;
        } else if (state == acceptedState &&
                   (character == 'b' || character == '2' || character == '_')) {
            continue;
        } else {
            cout << STUCK_IN_STATE_PREFIX_MSG << state << endl;
            return (false);
        }
    }

    // return true if string is accepted
    return state == acceptedState;
}//end of ident


// REAL DFA
// This FA is for RE: ** 2^*.3^+
bool real_token(string const &word) {
    unsigned int state = 0;
    unsigned int const acceptedState = 2;

    cout << IDENT_TYPE_START_MSG << endl;

    for (char const &character : word) {
        cout << CURRENT_STATE_PREFIX_MSG << state << endl;
        cout << CURRENT_CHAR_PREFIX_MSG << character << endl;

        // condition of transitions for the regular expression
        if (state == 0 && character == '2') {
            continue;
        } else if (state == 0 && character == '.') {
            state = 1;
        } else if ((state == 1 || state == acceptedState)
                   && character == '3') {
            state = acceptedState;
        } else {
            cout << STUCK_IN_STATE_PREFIX_MSG << state << endl;
            return (false);
        }
    }

    // return true if string is accepted
    return state == acceptedState;
}//end of real


//INT DFA
// This FA is for RE: ** 2^+
bool integer_token(string const &word) {
    unsigned int state = 0;
    unsigned int const acceptedState = 1;

    cout << IDENT_TYPE_START_MSG << endl;

    for (char const &character : word) {
        cout << CURRENT_STATE_PREFIX_MSG << state << endl;
        cout << CURRENT_CHAR_PREFIX_MSG << character << endl;

        // condition of transitions for the regular expression
        if (character == '2') {
            state = acceptedState;
        } else {
            cout << STUCK_IN_STATE_PREFIX_MSG << state << endl;
            return (false);
        }
    }

    // return true if string is accepted
    return state == acceptedState;
}// end of int

fstream fin;   // file stream to use

// Scanner sets the_type and w - TO BE COMPLETED **
int scanner(TOKEN_TYPE &the_type, string &w) {

    // This goes through all machines one by one on the input string w

    cout << endl;
    cout << ".....Scanner was called..." << endl;

    fin >> w;  // grab next word from fain.txt
    cout << ">>>>>Word is:" << w << endl;

    if (mytoken(w)) {
        the_type = MY_TOKEN;
    }

        // ** add other if-then's here in the right order to go through
        // ** all FAs one by one and set the_type to be IDENT, REAL or INT.

    else //none of the FAs returned TRUE
    {
        cout << ">>>>>Lexical Error: The string is not in my language" << endl;
        the_type = ERROR;
    }

}//the very end of scanner

// The test-driver -- NO NEED TO CHANGE THIS
int main() {
    string filename;
    TOKEN_TYPE thetype;
    string theword;

    cout << "Enter the input file name:";
    cin >> filename;
    fin.open(filename.c_str(), fstream::in);

    string tokens[5] = {"ERROR", "MY_TOKEN", "IDENT", "REAL", "INT"};

    while (true)  // keep on going
    {
        scanner(thetype, theword);  // the parameters will be set by Scanner
        if (theword == "EOF") break;

        cout << ">>>>>Type is:" << tokens[thetype] << endl;
    }

    cout << ">>>>>End of File encountered" << endl;
    fin.close();
}// end of main

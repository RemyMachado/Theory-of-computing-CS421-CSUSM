#include<iostream>
#include<fstream>
#include<string>
#include <sstream>

using namespace std;

#define TRANSITIONS_FILENAME "trs.txt"
#define DFAS_FILENAME "dfas.txt"
#define DISCLAIMER_PREFIX_MSG "This is a table driven scanner. Needs "
#define STATES_AND_CHAR_RULES_MSG "States are 0 to 9 and chars are a to d"
#define DONE_READING_MSG ".....done reading tables...."
#define ENTER_STRING_MSG "@@Enter a string: "
#define NO_TRANSITION -1
#define CHAR_NOT_SUPPORTED -1
#define COLUMN_LABELS_MSG "        a b c d"
#define DFA_INFO_INFIX_MSG " is start and ends in "
#define TRY_DFA_PREFIX_MSG "Trying dfa "
#define TRY_DFA_SUFFIX_MSG "--------"
#define STATE_PREFIX_MSG "state: "
#define CHAR_PREFIX_MSG " char: "
#define NEW_STATE_PREFIX_MSG "new state: "
#define FOUND_TOKEN_PREFIX_MSG "Found token "
#define EXIT_HELP_MSG "do control-C to quit"
#define LEXICAL_ERROR_MSG "Lexical error!"

//--------------------------------------
// CS421 File td.cpp for HW2B Table-Driven Scanner
// Your name: **Anthony Machado
//--------------------------------------

// info on each DFA
struct info {
    string name; // token name
    int startstate;
    int finalstate;
};

info DFAs[4];   // store up to 4 dfas' start and final

int TRS[10][4]; // store all trs's - states 0-9 and chars a b c d -- all dfas transitions are in here

// ----- utility functions -----------------------

// load/save the transitions and DFAs information necessary to the scanner
int readTables() {
    string lineDFA;
    string nameDFA;
    int startStateDFA;
    int endStateDFA;
    int countDFA = 0;
    ifstream transitionFileInput(TRANSITIONS_FILENAME, ios::in);
    ifstream DFAsFileInput(DFAS_FILENAME, ios::in);

    // load the content of the transitions file into a 2d array
    for (auto &transitionRow : TRS) {
        for (int &transition : transitionRow) {
            transitionFileInput >> transition;
        }
    }

    // load the content of the DFAs file into an array
    while (getline(DFAsFileInput, lineDFA)) {
        stringstream lineStream(lineDFA);
        lineStream >> nameDFA;
        lineStream >> startStateDFA;
        lineStream >> endStateDFA;

        // summarize information of the current DFA in a struct
        info infoDFA = {
                nameDFA,
                startStateDFA,
                endStateDFA
        };

        // save this information to the array
        DFAs[countDFA] = infoDFA;
        ++countDFA;
    }

    // return how many DFAs were read
    return countDFA;
}

// display the transitions and the existing DFAs information
void displayTables(int numDFAs) {
    cout << COLUMN_LABELS_MSG << endl;

    for (int i = 0; i < 10; ++i) {
        // display possible transitions for a given state
        cout << "State " << i << ":";
        for (auto const &givenState: TRS[i]) {
            if (givenState == NO_TRANSITION) {
                cout << ' ';
            } else {
                cout << givenState;
            }
            cout << ' ';
        }
        cout << endl;
    }

    // display DFAs information
    for (int i = 0; i < numDFAs; ++i) {
        auto const infoDFA = DFAs[i];

        cout << infoDFA.name << ": " <<
             infoDFA.startstate << DFA_INFO_INFIX_MSG << infoDFA.finalstate << endl;
    }
}

// return the new state depending on the input and the current state
int Transition(char character, int currentState) {
    int newState;
    int colNumber = character - 'a'; // convert char to index

    if (colNumber < 0 || colNumber >= 4) {
        return CHAR_NOT_SUPPORTED;
    }
    newState = TRS[currentState][colNumber]; // lookup the resulting state for the given input

    return newState;
}

// accept/reject a word for a given DFA
bool accept(info dfa, string word) {
    int state = dfa.startstate;

    // go to the next state in TRS table for each character of the given word
    for (auto const &character: word) {
        cout << STATE_PREFIX_MSG << state << CHAR_PREFIX_MSG << character << endl;
        state = Transition(character, state);
        cout << NEW_STATE_PREFIX_MSG << state << endl;

        if (state == CHAR_NOT_SUPPORTED || state == NO_TRANSITION) {
            return false; // word is rejected
        }
    }

    return state == dfa.finalstate; // accept if state is final
}

int main() {
    bool tokenRecognized;
    cout << DISCLAIMER_PREFIX_MSG << TRANSITIONS_FILENAME <<
         " and " << DFAS_FILENAME << "." << endl;
    cout << STATES_AND_CHAR_RULES_MSG << endl;

    int numDFA = readTables(); // how many DFAs were read
    displayTables(numDFA);
    cout << DONE_READING_MSG << endl;

    string word;
    while (true) {
        tokenRecognized = false;
        cout << ENTER_STRING_MSG;
        cin >> word;

        // check one by one if DFAs accept the word
        for (int i = 0; i < numDFA; ++i) {
            auto const infoDFA = DFAs[i];

            cout << TRY_DFA_PREFIX_MSG << i << TRY_DFA_SUFFIX_MSG << endl;
            if (accept(infoDFA, word)) {
                // display name of the recognized token
                cout << FOUND_TOKEN_PREFIX_MSG << infoDFA.name << endl;
                cout << EXIT_HELP_MSG << endl;
                tokenRecognized = true;
                break;
            }
        }

        // if no DFA does, generate a lexical error message.
        if (!tokenRecognized) {
            cout << LEXICAL_ERROR_MSG << endl;
            cout << EXIT_HELP_MSG << endl;
        }
    }

}//the end

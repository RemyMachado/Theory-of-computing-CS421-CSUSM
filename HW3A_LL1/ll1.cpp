#include<iostream>
#include<cstdlib>
#include<fstream>
#include<vector>
#include <stack>
#include<string>

using namespace std;

//---------------------------------------
// CS421 File ll1.cpp for HW3A LL1 Table-Driven Parser
// Your name: **Anthony Machado
//---------------------------------------

// Complete this to fit the HW3A specification - look for **
// Must have the same types of tracing couts as my demo program.

// Feel free to use a stack class or use a vector
// to implement your stack.  The stack will contain characters.

vector<char> M[3][2];
// 3 rows for S, A, B
// 2 rows for 0, 1
// Each slot contains a rule's right side
// which is a vector of characters

stack<char> charStack;

//  ------- conversion functions ------------------------


// to convert non-terms S, A, B to table rows 0, 1, 2
int toRow(char C) {
    // return row index of non-term character
    if (C == 'S') {
        return 0;
    } else if (C == 'A') {
        return 1;
    } else if (C == 'B') {
        return 2;
    }

    return -1;
}

// to convert '0' and '1' to table columns 0 and 1 
int toCol(char c) {
    // return column index of term character
    if (c == '0') {
        return 0;
    } else if (c == '1') {
        return 1;
    }

    return -1;
}

// to convert row 0, 1, 2 to non-terms S, A and B
char toNonterm(int r) {
    // return non-term character of row index
    if (r == 0) {
        return 'S';
    } else if (r == 1) {
        return 'A';
    } else if (r == 2) {
        return 'B';
    }

    return -1;
}

// ** Then complete the following functions.-----------------------------

// to display a rule's rhs which is in vector V
void displayVector(vector<char> V) {
    // display given production rules
    cout << "\t\t";
    for (auto const character : V) {
        cout << " " << character;
    }
}

// to read in the rules into M, make sure ; is not stored
void readrules() {
    ifstream fin("rules", ios::in);
    char lhs;
    char nextChar;
    int row;
    unsigned int nonTermRuleIndex;

    // For each line of "rules" (e.g. S  0 A 0 ;)
    // The first char of a line determines the row of M
    // The second char of a line determine the column of M
    // Note that each entry of M (the second char up to ;)
    // will be a vector representing
    // the right hand side of a rule (rhs)

    // loop while there is a production rule left
    while (fin >> lhs) {
        row = toRow(lhs); // set row index
        fin >> nextChar; // retrieve next rhs char from file
        nonTermRuleIndex = toCol(nextChar); // set col index

        // save each character of the rhs
        while (nextChar != ';') {
            M[row][nonTermRuleIndex].emplace_back(nextChar);
            fin >> nextChar;
        }
    }

    // ** Display the table nicely
    //    use toNonterm to show row labels (S, A, B)
    //    use displayVector for each content

    // display the table nicely
    for (std::size_t i = 0; i < 3; ++i) {
        cout << toNonterm(i) << ':'; // display lhs
        for (auto const &rule : M[i]) {
            displayVector(rule); // display rhs
        }
        cout << endl;
    }
}

//  pushes V contents to the stack 
void addtostack(vector<char> V) {
    cout << "adding rhs of a rule to the stack" << endl << endl;
    // **  be careful of the order
    // because 1 0 0 means 1 will be at the top of the stack

    // add production rule rhs in reverse order to the stack
    for (auto i = V.rbegin(); i != V.rend(); ++i) {
        charStack.emplace(*i);
    }
}

//  ------- helper functions ------------------------
void displayStack() {
    stack<char> charStackCopy(charStack);

    cout << "Stack" << endl;

    // display the stack vertically from top to bottom
    while (!charStackCopy.empty()) {
        cout << charStackCopy.top() << endl;
        charStackCopy.pop();
    }
    cout << "--------------" << endl;
}

void displayEmptyStack() {
    cout << "Stack" << endl <<
         "[ empty ]" << endl <<
         "--------------" << endl;
}

bool isTerm(char c) {
    // check if given char is terminal
    return toCol(c) != -1;
}
// ------- !helper functions ------------------------

int main() {
    char nextStackChar;

    readrules();  // M is filled and displayed

    string ss;
    cout << "Enter a string made of 0's and/or 1's: ";
    cin >> ss;

    // ** push 'S' onto the stack to start
    charStack.emplace('S');

    int i = 0;  // index for ss
    while (ss[i] != '\0')  // for each char of ss
    {
        // Based on ss[i] and
        //    the top of stack, update the stack:
        // ** note that empty stack will cause immediate failure
        // ** note that top of stack terminal and ss[i] mismatching
        //    will cause immediate failure
        // ** note that no entry in M for the top of stack (non-terminal)
        //    and ss[i] will cause immediate
        //    failure  (use toRow and toCol to look up M)
        // ** otherwise, addtoStack the M entry based on ss[i] and the top of stack

        if (charStack.empty()) {
            // handle empty stack case
            displayEmptyStack();
            cout << "current char is: " << ss[i] << endl;
            cout << ">>Error - stack is empty. Reject!" << endl;
            return 1;
        } else {
            displayStack();
        }

        nextStackChar = charStack.top(); // save the top char
        charStack.pop(); // remove the top char
        cout << "current char is: " << ss[i] << endl;

        if (!isTerm(ss[i])) {
            // handle unknown char
            cout << ">>Error - no rule. Reject!" << endl;

            return 1;
        }

        if (!isTerm(nextStackChar)) {
            // handle non-term char in the queue
            addtostack(M[toRow(nextStackChar)][toCol(ss[i])]);
            continue;
        } else if (ss[i] == nextStackChar) {
            // match()
            cout << "matched!" << endl;
        } else {
            // term char is not matching
            cout << ">>Mismatch error. Reject!" << endl;

            return 1;
        }
        cout << endl;
        ++i;
    } // end of string


    // ** Here, check for success for failure based on stack empty or not
    if (charStack.empty()) {
        // input is fully accepted
        displayEmptyStack();
        cout << ">>Accept!" << endl << endl;

        return 0;
    }

    // stack not empty -> input is rejected
    displayStack();
    cout << ">>Reject! input too short" << endl;

    return 1;
}// end of main

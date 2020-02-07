#include<iostream>
#include<string>

using namespace std;

//-------------------------------------------------------
// CS421 HW1
// Write a recognizer in C++ for L = {x | x is a binary number}.
// Your name: **Anthony Machado
//-------------------------------------------------------

#define PROGRAM_SUCCESS 0
#define ALPHABET "01"
#define RECOGNIZED_MSG "YES IN L"
#define REJECTED_MSG "NO NOT IN L"

void PrintRecognition() {
    cout << RECOGNIZED_MSG << endl;
}

void PrintRejection() {
    cout << REJECTED_MSG << endl;
}

/* Recognizer  for L = { x | x is a binary number } */
bool recognizer(string s) {
    // reject if it's an empty string
    if (s.empty()) {
        return false;
    }

    // reject if a character does not belong to the alphabet
    return s.find_first_not_of(ALPHABET) == string::npos;
}

int main() {
    string line;

    while (std::getline(cin, line)) {
        // test if the given element is belonging to the language
        if (recognizer(line)) {
            PrintRecognition();
        } else {
            PrintRejection();
        }
    }

    return PROGRAM_SUCCESS;
}


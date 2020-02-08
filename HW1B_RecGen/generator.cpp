#include <iostream>
#include <string>
#include <queue>

using namespace std;
// ** include queue.h or equivalent such as <queue>

//----------------------------------------------
// CS421 HW1
// Write a generator in C++ for L = {x | x is a binary number}.
// Your name: **Anthony Machado
//----------------------------------------------

#define PROGRAM_SUCCESS 0
#define ALPHABET_RECOGNIZED "01"
#define ALPHABET_STRING_GENERATION "012"

/* Recognizer  for L = { x | x is a binary number } */
bool recognizer(string s) {
    // reject if it's an empty string
    if (s.empty()) {
        return false;
    }

    // reject if a character does not belong to the alphabet
    return s.find_first_not_of(ALPHABET_RECOGNIZED) == string::npos;
}

void PrintFirstChar() {
    cout << ALPHABET_STRING_GENERATION[0] << std::endl;
}

int main() {
    queue<string> generationQueue;
    auto alphabetStringGeneration = string(ALPHABET_STRING_GENERATION);

    if (string(ALPHABET_STRING_GENERATION).empty()) {
        return PROGRAM_SUCCESS;
    }

    // print it, because it should not be pushed to the queue
    PrintFirstChar();

    // populate the queue with the alphabet, except the first char
    for (auto it = alphabetStringGeneration.begin() + 1; it < alphabetStringGeneration.end(); ++it) {
        generationQueue.push(string(1, *it));
    }

    for (int i = 0; i < 2000; ++i) {
        string poppedValue = generationQueue.front();
        generationQueue.pop();
        cout << poppedValue << std::endl;

        for (auto it = alphabetStringGeneration.begin(); it < alphabetStringGeneration.end(); ++it) {
            generationQueue.push(poppedValue + *it);
        }

        // ** generate a string
        // ** if the recognizer says true, display it
    }

    return PROGRAM_SUCCESS;
}

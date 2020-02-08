#include <iostream>
#include <string>
#include <queue>

using namespace std;

//----------------------------------------------
// CS421 HW1
// Write a generator in C++ for L = {x | x is a binary number}.
// Your name: **Anthony Machado
//----------------------------------------------

#define PROGRAM_SUCCESS 0
#define ALPHABET_RECOGNIZED "01"
#define ALPHABET_STRING_GENERATION "012"
#define RECOGNIZED_MSG_SUFFIX " is binary"

void PrintRecognition(string const &value) {
    cout << value << RECOGNIZED_MSG_SUFFIX << endl;
}

/* Recognizer  for L = { x | x is a binary number } */
bool recognizer(string s) {
    // reject if it's an empty string
    if (s.empty()) {
        return false;
    }

    // reject if a character does not belong to the alphabet
    return s.find_first_not_of(ALPHABET_RECOGNIZED) == string::npos;
}

int main() {
    queue<string> generationQueue;
    auto alphabetStringGeneration = string(ALPHABET_STRING_GENERATION);

    if (alphabetStringGeneration.empty()) {
        return PROGRAM_SUCCESS;
    }

    // generate |E| first elements. i.e. populate the queue with the alphabet
    for (auto const &element : alphabetStringGeneration) {
        generationQueue.push(string(1, element));
    }

    // infinite loop, because "The user must somehow interactively terminate"
    while (true) {
        // retrieve the oldest generated string and remove it from the storage
        string poppedValue = generationQueue.front();
        generationQueue.pop();

        // display oldest generated string if recognized
        if (recognizer(poppedValue)) {
            PrintRecognition(poppedValue);
        }

        // generate next |E| strings and put them in the storage
        for (auto const &element : alphabetStringGeneration) {
            generationQueue.push(poppedValue + element);
        }
    }

    return PROGRAM_SUCCESS;
}

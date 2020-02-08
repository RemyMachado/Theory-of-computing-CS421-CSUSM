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
#define ALPHABET "01"

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
    queue<string> generationQueue;

    cout << '0' << std::endl;
    generationQueue.push("1");
    generationQueue.push("2");

    for (int i = 0; i < 1000; ++i) {
        string poppedValue = generationQueue.front();
        generationQueue.pop();
        cout << poppedValue << std::endl;

        generationQueue.push(poppedValue + '0');
        generationQueue.push(poppedValue + '1');

        string lastToPush = poppedValue + '2';
        generationQueue.push(lastToPush);


        // ** generate a string
        // ** if the recognizer says true, display it
    }

    return PROGRAM_SUCCESS;
}

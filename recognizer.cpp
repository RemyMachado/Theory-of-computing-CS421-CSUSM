#include <iostream>
#include <string>

#define MINIMUM_MAIN_PARAMETERS_COUNT 2
#define MAIN_PARAMETER_INDEX_TO_TEST 1
#define PROGRAM_SUCCESS 0
#define ALPHABET "01"
#define RECOGNIZED_MSG "YES IN L"
#define REJECTED_MSG "NO NOT IN L"

void PrintRecognition() {
    std::cout << RECOGNIZED_MSG << std::endl;
}

void PrintRejection() {
    std::cout << REJECTED_MSG << std::endl;
}

/* Recognizer  for L = { x | x is a binary number } */
bool IsRecognized(std::string const &element) {
    // reject if a letter does not belong to the alphabet
    return element.find_first_not_of(ALPHABET) == std::string::npos;
}

int main(int argc, char **argv) {
    // reject if a null parameter was given and exit program
    if (argc < MINIMUM_MAIN_PARAMETERS_COUNT) {
        PrintRejection();
        return PROGRAM_SUCCESS;
    }

    // test if the given element is belonging to the language
    if (IsRecognized(argv[MAIN_PARAMETER_INDEX_TO_TEST])) {
        PrintRecognition();
    } else {
        PrintRejection();
    }

    return PROGRAM_SUCCESS;
}

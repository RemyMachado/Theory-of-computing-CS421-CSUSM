#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

//--------------------------------------
// CS421 File mat.cpp for HW2A Matrix Practice
// Your name: **Anthony Machado
//--------------------------------------

#define FILE_NAME "lines.txt"

// the following can be changed and the rest of the code should work
int const R = 3;  // number of rows
int const C = 4;  // number of columns
int const VM = 3; // table entry (vector) length

vector<char> T[R][C];  // 3 rows and 4 columns table for now

// ------------------ Functions --------------------------------

// convert a to 0, b to 1, c to 2 etc.
int convert(char x) {
    return x - 'a';
}

int readTable() {
    int row; // row and col numbers
    int col;
    char col_c; // column indicator
    ifstream fileStream(FILE_NAME, ios::in);

    // Read in the file into T
    while (fileStream >> row)
    {
        fileStream >> col_c;
        col = convert(col_c);  // convert to a slot number
        vector<char> v;  // a vector to fill
        char c; // one char from the file

        // fill v with chars from the file (there are VM chars)
        for (unsigned int i = 0; i < VM; ++i) {
            fileStream >> c;
            v.push_back(c);
        }
        // Put  v in T[row][col]
        T[row][col] = v;
    }
}

// Displays a vector or "---" if the vector is empty or the content if exists
void showVector(vector<char> v) {
    if (v.size() == 0)  // empty entry
        for (int i = 1; i <= VM; i++) cout << "- ";
    else {
        // show the content of v separated by blanks (e.g. "a b c")
        for (auto it = v.begin(); it != v.end(); ++it) {
            std::cout << *it << ' ';
        }
    }
}

// Displays T as a table, separating entries with "|"
void displayTable() {
    // display T nicely labeled with row numbers (without column numbers)
    for (unsigned int i = 0; i < R; ++i) {
        std::cout << i;
        for (unsigned int j = 0; j < C; ++j) {
            std::cout << "| ";
            showVector(T[i][j]);
        }
        std::cout << std::endl;
    }
}

int main() {
    cout << "Reading table from " << FILE_NAME << "..." << endl;
    readTable();
    displayTable();

    return 0;
}
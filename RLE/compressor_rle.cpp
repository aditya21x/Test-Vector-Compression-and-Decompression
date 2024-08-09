#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

char getCharFromBinary(const string& binarySubstr) {
    const char charMap[32] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F'
    };
    int index = 0;
    for (int i = 0; i < 5; ++i) {
        index = (index << 1) | (binarySubstr[i] - '0');
    }
    return charMap[index];
}

string runLengthEncode(const string& input) {
    string encoded;
    if (input.size() < 5) {
        return encoded;  // Handle case where input is less than 5 bits
    }

    char currentChar = getCharFromBinary(input.substr(0, 5));
    int runLength = 1;

    for (size_t i = 5; i < input.size(); i += 5) {
        if (i + 5 > input.size()) break;  // Prevent out of bounds access

        char nextChar = getCharFromBinary(input.substr(i, 5));
        if (nextChar != currentChar) {
            encoded += currentChar + (runLength > 1 ? to_string(runLength) : "");
            currentChar = nextChar;
            runLength = 1;
        } else {
            runLength++;
        }
    }

    // Append the last character and its count if necessary
    encoded += currentChar + (runLength > 1 ? to_string(runLength) : "");
    return encoded;
}

string readAndReplaceInput(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string content, line;
    while (getline(file, line)) {
        for (char& c : line) {
            if (c == '2') {
                c = '0';
            }
        }
        content += line;
    }
    file.close();
    return content;
}

int main() {
    string inputFileName = "input.txt";
    string compressedFileName = "compressor_rle.txt";

    string input = readAndReplaceInput(inputFileName);
    string encodedString = runLengthEncode(input);

    ofstream outFile(compressedFileName);
    if (!outFile.is_open()) {
        cerr << "Error opening file for writing: " << compressedFileName << endl;
        return 1;
    }

    outFile << encodedString;
    outFile.close();

    cout << "Compression completed. Data written to " << compressedFileName << endl;
    return 0;
}

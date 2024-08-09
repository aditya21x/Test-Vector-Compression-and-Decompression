#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string decode(const string& encoded) {
    string mapping = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string binaryMapping[52] = {
        "00000", "00001", "00010", "00011", "00100", "00101", "00110", "00111",
        "01000", "01001", "01010", "01011", "01100", "01101", "01110", "01111",
        "10000", "10001", "10010", "10011", "10100", "10101", "10110", "10111",
        "11000", "11001", "11010", "11011", "11100", "11101", "11110", "11111"
    };

    string decoded;
    int i = 0;

    while (i < encoded.length()) {
        char currentChar = encoded[i++];
        int binaryIndex = -1;

        if (currentChar >= 'a' && currentChar <= 'z') {
            binaryIndex = currentChar - 'a';
        } else if (currentChar >= 'A' && currentChar <= 'F') {
            binaryIndex = currentChar - 'A' + 26;
        } else {
            // Invalid character
            cerr << "Invalid character found: " << currentChar << endl;
            return "Invalid input.";
        }

        // Read the decimal number
        int repeatCount = 0;
        while (i < encoded.length() && isdigit(encoded[i])) {
            repeatCount = repeatCount * 10 + (encoded[i++] - '0');
        }

        // Append the binary value to the decoded string efficiently
        decoded.reserve(decoded.size() + repeatCount * 5); // Reserve memory for efficiency
        for (int j = 0; j < repeatCount; ++j) {
            decoded += binaryMapping[binaryIndex];
        }
    }

    return decoded;
}

int main() {
    string compressedFileName = "compressor_rle.txt";
    string outputFileName = "output_rle.txt";

    // Reading from the compressed file
    ifstream inputFile(compressedFileName);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file: " << compressedFileName << endl;
        return 1;
    }

    string encoded;
    getline(inputFile, encoded);
    inputFile.close();

    // Decode the encoded string
    string decoded = decode(encoded);

    // Writing the decoded data to the output file
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Error opening output file: " << outputFileName << endl;
        return 1;
    }

    outputFile << decoded;
    outputFile.close();

    cout << "Decompression completed. Data written to " << outputFileName << endl;

    return 0;
}

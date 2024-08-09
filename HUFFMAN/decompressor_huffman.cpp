#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

// Decode using Huffman codes
string huffmanDecode(const string& encoded, unordered_map<string, char>& reverseCodes) {
    string decoded;
    string buffer;
    for (char bit : encoded) {
        buffer += bit;
        if (reverseCodes.find(buffer) != reverseCodes.end()) {
            decoded += reverseCodes[buffer];
            buffer.clear();
        }
    }
    return decoded;
}

// Load Huffman codes from a file
void loadHuffmanCodes(const string& filename, unordered_map<char, string>& codes, unordered_map<string, char>& reverseCodes) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    char ch;
    string code;
    while (file >> ch >> code) {
        codes[ch] = code;
        reverseCodes[code] = ch;
    }
    file.close();
}

int main() {
    string huffmanCompressedFileName = "compressor_huffman.txt";
    string huffmanCodesFileName = "huffman_code.txt";
    string outputFileName = "output_huffman.txt";

    ifstream inputFile(huffmanCompressedFileName);
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << huffmanCompressedFileName << endl;
        return 1;
    }

    string encoded;
    getline(inputFile, encoded);
    inputFile.close();

    unordered_map<char, string> huffmanCodes;
    unordered_map<string, char> reverseCodes;
    loadHuffmanCodes(huffmanCodesFileName, huffmanCodes, reverseCodes);

    string decoded = huffmanDecode(encoded, reverseCodes);

    ofstream outFile(outputFileName);
    if (!outFile.is_open()) {
        cerr << "Error opening file for writing: " << outputFileName << endl;
        return 1;
    }

    outFile << decoded;
    outFile.close();

    cout << "Decompression completed. Data written to " << outputFileName << endl;

    return 0;
}

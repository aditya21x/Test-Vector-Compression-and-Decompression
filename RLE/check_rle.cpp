#include <iostream>
#include <fstream>

using namespace std;

long getFileSize(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate); // Open file in binary mode and move to end
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    return file.tellg(); // Get the size of the file
}

int main() {
    string inputFileName = "input.txt"; // Input file with binary test vectors
    string outputFileName = "output_rle.txt"; // Output file for compressed data

    long originalSize = getFileSize(inputFileName);
    long compressedSize = getFileSize(outputFileName);

    cout << "Original file size: " << originalSize << " bytes" << endl;
    cout << "Compressed file size: " << compressedSize << " bytes" << endl;

    if (compressedSize < originalSize) {
        cout << "Compression successful. File size reduced by " << (originalSize - compressedSize) << " bytes." << endl;
    } else if (compressedSize == originalSize) {
        cout << "Compression resulted in no size reduction." << endl;
    } else {
        cout << "Compression was not effective. File size increased by " << (compressedSize - originalSize) << " bytes." << endl;
    }
    cout<<"Total efficiency is "<<double((originalSize - compressedSize)*100 / originalSize) <<" %"<<endl;
    return 0;
}

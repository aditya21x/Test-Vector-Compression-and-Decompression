#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>

using namespace std;

struct Node {
    char ch;
    unsigned freq;
    Node *left, *right;
    Node(char c, unsigned f, Node *l = nullptr, Node *r = nullptr)
        : ch(c), freq(f), left(l), right(r) {}
};

// Comparison operator for the priority queue
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Generate the Huffman coding tree
Node* buildHuffmanTree(const unordered_map<char, unsigned>& frequencies) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (const auto& pair : frequencies) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        Node *left = minHeap.top(); minHeap.pop();
        Node *right = minHeap.top(); minHeap.pop();
        Node *top = new Node('\0', left->freq + right->freq, left, right);
        minHeap.push(top);
    }

    return minHeap.top();
}

// Generate Huffman codes
void generateHuffmanCodes(Node* root, const string& str, unordered_map<char, string>& codes) {
    if (!root) return;
    if (root->ch != '\0') {
        codes[root->ch] = str;
    }
    generateHuffmanCodes(root->left, str + "0", codes);
    generateHuffmanCodes(root->right, str + "1", codes);
}

// Encode the input using Huffman codes
string huffmanEncode(const string& input, unordered_map<char, string>& codes) {
    string encoded;
    for (char ch : input) {
        encoded += codes[ch];
    }
    return encoded;
}

// Save Huffman codes to a file
void saveHuffmanCodes(const unordered_map<char, string>& codes, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    for (const auto& pair : codes) {
        file << pair.first << " " << pair.second << endl;
    }
    file.close();
}

int main() {
    string rleCompressedFileName = "compressor_rle.txt";
    string huffmanCompressedFileName = "compressor_huffman.txt";
    string huffmanCodesFileName = "huffman_code.txt";

    ifstream inputFile(rleCompressedFileName);
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << rleCompressedFileName << endl;
        return 1;
    }

    string input;
    getline(inputFile, input);
    inputFile.close();

    unordered_map<char, unsigned> frequencies;
    for (char ch : input) {
        frequencies[ch]++;
    }

    Node* root = buildHuffmanTree(frequencies);
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    string encodedString = huffmanEncode(input, huffmanCodes);

    saveHuffmanCodes(huffmanCodes, huffmanCodesFileName);

    ofstream outFile(huffmanCompressedFileName);
    if (!outFile.is_open()) {
        cerr << "Error opening file for writing: " << huffmanCompressedFileName << endl;
        return 1;
    }

    outFile << encodedString;
    outFile.close();

    cout << "Huffman Compression completed. Data written to " << huffmanCompressedFileName << endl;

    return 0;
}

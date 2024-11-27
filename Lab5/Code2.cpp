#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <bitset>
#include <iostream>
using namespace std;

// Define a node for the Huffman Tree
struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    
    HuffmanNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

// Comparator for the priority queue (min-heap)
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

// Function to build the Huffman Tree
HuffmanNode* buildHuffmanTree(const string& text) {
    unordered_map<char, int> frequencyMap;
    
    // Calculate frequency of each character
    for (char ch : text) {
        if (isalpha(ch)) { // Only letters
            frequencyMap[ch]++;
        }
    }
    
    // Priority queue to build the tree based on frequency
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;
    
    // Insert each character and its frequency as a node into the minHeap
    for (const auto& pair : frequencyMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }
    
    // Build the Huffman Tree
    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();
        
        HuffmanNode* merged = new HuffmanNode('\0', left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;
        minHeap.push(merged);
    }
    
    return minHeap.top();
}

// Function to generate Huffman Codes
void generateCodes(HuffmanNode* root, const string& code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;
    
    if (root->character != '\0') { // Leaf node
        huffmanCodes[root->character] = code;
    }
    
    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

// Function to compress text using Huffman coding
string compress(const string& text, unordered_map<char, string>& huffmanCodes) {
    string compressedText;
    for (char ch : text) {
        if (huffmanCodes.find(ch) != huffmanCodes.end()) {
            compressedText += huffmanCodes[ch];
        }
    }
    return compressedText;
}

// Function to calculate compression ratio
void calculateCompressionRatio(const string& originalText, const string& compressedText) {
    int originalSize = originalText.length() * 8; // Each character is 8 bits
    int compressedSize = compressedText.length(); // Already in bits
    cout << "Original size (in bits): " << originalSize << endl;
    cout << "Compressed size (in bits): " << compressedSize << endl;
    cout << "Compression ratio: " << (double)compressedSize / originalSize << endl;
}

int main() {
    string text;
    cout << "Enter the text to compress: ";
    getline(cin, text);
    
    // Build Huffman Tree and generate codes
    HuffmanNode* root = buildHuffmanTree(text);
    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);
    
    // Display Huffman Codes for each letter
    cout << "Huffman Codes:\n";
    for (const auto& pair : huffmanCodes) {
        cout << "'" << pair.first << "': " << pair.second << endl;
    }
    
    // Compress the text
    string compressedText = compress(text, huffmanCodes);
    
    // Display compression ratio
    calculateCompressionRatio(text, compressedText);

    return 0;
}

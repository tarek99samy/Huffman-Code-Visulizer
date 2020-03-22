#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Struct to contain node details
struct node {
public:
    char symbol;
    long long frequency;
    node * left;
    node * right;

    // operator overloading for internal comparison in priorty queue
    bool operator < (const node cmp) const {
        return frequency > cmp.frequency;
    }
};

// used variables in functions	and constants
const int MAX_TREE_SIZE = 10000;
const char PARENT = '-';		/* Our choosen special character to represent parent nodes */

ifstream infile("input.txt");
ofstream  binaryfile("BinaryCodes.txt"), outfile("output.txt");

map<char, uint8_t> encode;
map<uint8_t, char> decode;

vector<uint8_t> output;
vector<node> Nodes(MAX_TREE_SIZE);


map<char, node> getFrequencies(string text) {
    /*
        text : the input file data as continuous string
        operation : this function should calculate the frequency of each character in the input file
        return type : it returns a map {[char] -> node}
    */
    map<char, node> freq;
    for (int i = 0; i < text.length(); i++)
    {
        freq[text[i]].symbol = text[i];
        freq[text[i]].frequency++;
    }

    return freq;
}


priority_queue<node> constructPriorityQueue(map<char, node> nodes) {
    /*
        nodes : it is the output of getFrequency function ,
                and contains the frequency of each character in the input file
        return type : priority queue the contains the nodes sorted in ascending order
    */
    priority_queue<node> PriorityQueue;
    for (auto node : nodes) {
        PriorityQueue.push(node.second);
    }
    return PriorityQueue;
}


node constructHuffman(priority_queue<node> PriorityQueue) {
    /*
        nodes : the output  of construction of priority queue,
                it contains the nodes sorted in ascending order
        operation : this function follow the Huffman algorithm to construct the min-heap
        return type : returns the root of the Huffman-Heap
    */
    int indx = 0;
    while (PriorityQueue.size() > 1)
    {
        node NewParetnNode, node1, node2;

        node1 = PriorityQueue.top();
        PriorityQueue.pop();
        node2 = PriorityQueue.top();
        PriorityQueue.pop();

        Nodes[indx] = node1;
        indx++;
        Nodes[indx] = node2;
        indx++;

        NewParetnNode.frequency = node1.frequency + node2.frequency;
        NewParetnNode.symbol = PARENT;
        NewParetnNode.left = &Nodes[indx - 2];
        NewParetnNode.right = &Nodes[indx - 1];
        PriorityQueue.push(NewParetnNode);
    }

    return PriorityQueue.top();
}



void getCode(node* root, string code) {
    /*
        root : the current node in Huffman-Tree
        code : the code of the current node

        operation : claculating the code of the current node ,
                and make recursive calls for each child of node
    */
    if (root == nullptr)return;
    if (root->symbol != PARENT) {
        uint8_t x = 0;
        int j = 0;
        for (int i = 0; i < code.size(); i++) {
            if (code[i] == '1') {
                x += pow(2, j);
            }
            j++;
        }
        encode[root->symbol] = x;
        decode[x] = root->symbol;

        // fill in the file that contains all binary codes of characters in input file
        binaryfile << code<<" "<<root->symbol << "\n";
        return;
    }

    getCode(root->left, code + "0");
    getCode(root->right, code + "1");
}

void encodeHuffman(string text) {
    /*
        text : the input file data as continuous string
        this function should do the following:
            1- call function to calculate the frequency of each character
            2- call function to fill in the priority queue used in huffman algorithm
            3- call function to construct the huffman heap
            4- call function to fill in the two global maps (encode,decode)
    */
    map<char, node> Frequencies = getFrequencies(text);
    priority_queue<node> ProrityQueue = constructPriorityQueue(Frequencies);
    node Huffman_Heap_Root = constructHuffman(ProrityQueue);
    getCode(&Huffman_Heap_Root, "");
}


int main() {
    // Text : take all inputfile data first in a string to encode
    // combarison : store the output as a text also to compare with the taken data from
    //				file and validate the encoding and decoding processes
    string text, comparison;


    if (infile.is_open()) {
        while (getline(infile, text))
        {
        }
        infile.close();
    }
    else {
        cout << "INPUT FILE NOT FOUND!\n";
        return 0;
    }
    // call to encoding function
    encodeHuffman(text);

    // output: vector of Unsigned int byte to store the encoded bytes
    for (int i = 0; i < text.size(); i++) {
        output.push_back(encode[text[i]]);
    }

    // populate the output file and validate the algorithm

    if (outfile.is_open()) {
        for (int i = 0; i < output.size(); i++) {
            comparison += (unsigned  char)decode[output[i]];
        }
        outfile << comparison << endl;
        outfile.close();
    }
    else {
        cout << "OUTPUT FILE NOT FOUND!\n";
        return 0;
    }

    if (comparison == text)cout << "GOOD  JOB!\n";
    else cout << "NOT EQUAL\n";

    return 0;
}
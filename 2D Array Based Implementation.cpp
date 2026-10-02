#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Define constraints based on memory requirements
const int MAX_NODES = 100005; // Maximum total characters across all unique prefixes
const int ALPHABET_SIZE = 26; // For 'a' through 'z'

// The 2D Array: rows are nodes, columns are characters
int trie[MAX_NODES][ALPHABET_SIZE];

// Companion array to track the end of words or count of words ending at a node
int word_count[MAX_NODES];

// Counter to allocate a unique ID to every new row/node
int node_counter = 0;

/**
 * Inserts a string into the Trie
 */
void insert(const string& word) {
    int current_node = 0; // Start at ROOT
    
    for (char ch : word) {
        int char_idx = ch - 'a'; // Map character to column index (0-25)
        
        // If the path does not exist, create a new node ID
        if (trie[current_node][char_idx] == 0) {
            trie[current_node][char_idx] = ++node_counter;
        }
        
        // Move to the next node
        current_node = trie[current_node][char_idx];
    }
    
    // Mark the final node as the end of a word
    word_count[current_node]++;
}

/**
 * Searches for an exact string in the Trie
 */
bool search(const string& word) {
    int current_node = 0; // Start at ROOT
    
    for (char ch : word) {
        int char_idx = ch - 'a';
        
        // If the path breaks, the word doesn't exist
        if (trie[current_node][char_idx] == 0) {
            return false;
        }
        
        current_node = trie[current_node][char_idx];
    }
    
    // Return true if at least one word ended at this node
    return word_count[current_node] > 0;
}

/**
 * Checks if there is any word in the Trie that starts with the given prefix
 */
bool startsWith(const string& prefix) {
    int current_node = 0; // Start at ROOT
    
    for (char ch : prefix) {
        int char_idx = ch - 'a';
        
        if (trie[current_node][char_idx] == 0) {
            return false;
        }
        
        current_node = trie[current_node][char_idx];
    }
    
    // If we safely reached the end of the prefix, it exists
    return true;
}

int main() {
    // Insert words
    insert("apple");
    insert("app");
    
    // Test exact lookups
    cout << "Search 'apple': " << (search("apple") ? "Found" : "Not Found") << endl; // Found
    cout << "Search 'app': " << (search("app") ? "Found" : "Not Found") << endl;     // Found
    cout << "Search 'apr': " << (search("apr") ? "Found" : "Not Found") << endl;     // Not Found

    // Test prefix lookups
    cout << "StartsWith 'ap': " << (startsWith("ap") ? "Yes" : "No") << endl;       // Yes
    cout << "StartsWith 'bat': " << (startsWith("bat") ? "Yes" : "No") << endl;     // No

    return 0;
}

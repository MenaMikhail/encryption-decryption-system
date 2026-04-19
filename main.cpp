/*
   Name: Mena Mikhail
   Class: Network Security (CSCI-4400)
   Program: (Symmetric Encryption/Decryption)This program demonstrates two encryption techniques (polyalphabetic and rail fence), reads plaintext from a file, encrypts and decrypts it using both methods,
   and writes the results to an output file while taking one parameter (rail depth) from the user.  
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to apply M1 (Right Shift by 8)
// This function shifts a letter 8 positions to the right in the alphabet
char applyM1(char c) {
    return 'a' + (c - 'a' + 8) % 26;
}

// Function to apply M2 (Substitution Cipher)
// This function substitutes the letter based on a predefined substitution table
char applyM2(char c) {
    string plain = "abcdefghijklmnopqrstuvwxyz"; // Plain alphabet
    string cipher = "dkvqfgbxwpescjhtmyaulroizn"; // Substitution cipher
    return cipher[plain.find(c)]; // Return the corresponding substituted character
}

// Function to apply M3 (Right Shift by 14)
// This function shifts a letter 14 positions to the right in the alphabet
char applyM3(char c) {
    return 'a' + (c - 'a' + 14) % 26;
}

// Reverse M1 (Left Shift by 8)
// This function undoes the M1 operation by shifting the letter 8 positions to the left
char reverseM1(char c) {
    return 'a' + (c - 'a' + 18) % 26;
}

// Reverse M2 (Substitution Cipher)
// This function undoes the M2 substitution using the inverse substitution table
char reverseM2(char c) {
    string plain = "abcdefghijklmnopqrstuvwxyz"; // Plain alphabet
    string cipher = "dkvqfgbxwpescjhtmyaulroizn"; // Substitution cipher
    return plain[cipher.find(c)]; // Return the corresponding original character
}

// Reverse M3 (Left Shift by 14)
// This function undoes the M3 operation by shifting the letter 14 positions to the left
char reverseM3(char c) {
    return 'a' + (c - 'a' + 12) % 26;
}

// Polyalphabetic Encryption
// Encrypts the text using a sequence of transformations (M1, M2, M3)
string polyEncrypt(const string &text) {
    string encrypted = ""; // To store the encrypted text
    int cycle[] = {1, 2, 3}; // Cycle definitions for M1, M2, M3 (fixed to 3, not 4)
    int cycleIndex = 0; // To track the current transformation in the cycle

    // Loop through each character in the text
    for (char c : text) {
        if (isalpha(c) && islower(c)) { // Process only lowercase letters
            // Apply the corresponding transformation based on the cycle
            if (cycle[cycleIndex] == 1)
                encrypted += applyM1(c);
            else if (cycle[cycleIndex] == 2)
                encrypted += applyM2(c);
            else
                encrypted += applyM3(c);
            cycleIndex = (cycleIndex + 1) % 3; // Move to the next cycle index (fixed to 3)
        } else {
            encrypted += c; // If it's not a lowercase letter, just add it unchanged
        }
    }
    return encrypted; // Return the encrypted string
}

// Polyalphabetic Decryption
// Decrypts the encrypted text using the reverse transformations (reverse M1, reverse M2, reverse M3)
string polyDecrypt(const string &text) {
    string decrypted = ""; // To store the decrypted text
    int cycle[] = {1, 2, 3}; // Cycle definitions for reverse M1, reverse M2, reverse M3 (fixed to 3, not 4)
    int cycleIndex = 0; // To track the current transformation in the cycle

    // Loop through each character in the encrypted text
    for (char c : text) {
        if (isalpha(c) && islower(c)) { // Process only lowercase letters
            // Apply the corresponding reverse transformation based on the cycle
            if (cycle[cycleIndex] == 1)
                decrypted += reverseM1(c);
            else if (cycle[cycleIndex] == 2)
                decrypted += reverseM2(c);
            else
                decrypted += reverseM3(c);
            cycleIndex = (cycleIndex + 1) % 3; // Move to the next cycle index (fixed to 3)
        } else {
            decrypted += c; // If it's not a lowercase letter, just add it unchanged
        }
    }
    return decrypted; // Return the decrypted string
}

// Rail Fence Encryption
// Encrypts the text by writing it in a zigzag pattern across 'depth' number of rails
string railFenceEncrypt(string text, int depth) {
    vector<string> fence(depth, ""); // Create 'depth' number of rails (empty strings)
    int row = 0, dir = 1; // Initialize row and direction (1 = moving down, -1 = moving up)

    // Place characters in the appropriate rows based on the zigzag pattern
    for (char c : text) {
        fence[row] += c;
        row += dir; // Move to the next row
        if (row == depth - 1 || row == 0) dir *= -1; // Change direction at the top or bottom rail
    }

    // Concatenate all rows to form the encrypted message
    string cipher = "";
    for (const string &s : fence) cipher += s;
    return cipher; // Return the Rail Fence encrypted string
}

// Rail Fence Decryption
// Decrypts the Rail Fence cipher by reversing the zigzag process
string railFenceDecrypt(string cipher, int depth) {
    vector<vector<char>> rail(depth, vector<char>(cipher.length(), '\n')); // Create a 2D array for rails
    int row = 0, dir = 1;

    // Mark the zigzag pattern for the cipher text
    for (size_t i = 0; i < cipher.length(); i++) {
        rail[row][i] = '*';
        row += dir; // Move to the next row
        if (row == 0 || row == depth - 1) dir *= -1; // Change direction at the top or bottom rail
    }

    // Fill the marked positions in the array with the cipher text
    size_t index = 0;
    for (int i = 0; i < depth; i++) {
        for (size_t j = 0; j < cipher.length(); j++) {
            if (rail[i][j] == '*' && index < cipher.length()) {
                rail[i][j] = cipher[index++];
            }
        }
    }

    // Read the text in zigzag pattern from the 2D array to recover the original message
    string result = "";
    row = 0;
    dir = 1;
    for (size_t i = 0; i < cipher.length(); i++) {
        result += rail[row][i];
        row += dir;
        if (row == 0 || row == depth - 1) dir *= -1; // Change direction at the top or bottom rail
    }

    return result; // Return the decrypted Rail Fence string
}

int main() {
    string text; // To store the input text
    ifstream inFile("input.txt"); // Open input file for reading
    ofstream outFile("output.txt"); // Open output file for writing

    if (!inFile.is_open()) {
        cerr << "Error opening input.txt\n"; // Error if input file can't be opened
        return 1;
    }

    getline(inFile, text); // Read the input text from the file
    transform(text.begin(), text.end(), text.begin(), ::tolower); // Ensure the text is in lowercase

    // Polyalphabetic Cipher Encryption and Decryption
    string encrypted = polyEncrypt(text); // Encrypt the text using Polyalphabetic cipher
    string decrypted = polyDecrypt(encrypted); // Decrypt the encrypted text back to original

    // Output Polyalphabetic results to file
    outFile << "Polyalphabetic Encrypted: " << encrypted << endl;
    outFile << "Polyalphabetic Decrypted: " << decrypted << endl;

    // Rail Fence Cipher Encryption and Decryption
    int depth; // To store the depth (number of rails) for Rail Fence cipher
    cout << "Enter Rail Fence depth: ";
    cin >> depth; // Get depth from user input

    // Encrypt and decrypt using Rail Fence cipher with user-provided depth
    string rfEncrypted = railFenceEncrypt(text, depth);
    string rfDecrypted = railFenceDecrypt(rfEncrypted, depth);

    // Output Rail Fence results to file
    outFile << "Rail Fence Encrypted: " << rfEncrypted << endl;
    outFile << "Rail Fence Decrypted: " << rfDecrypted << endl;

    inFile.close(); // Close input file
    outFile.close(); // Close output file

    return 0; // Program successfully completed
}

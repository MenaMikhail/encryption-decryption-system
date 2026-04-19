# encryption-decryption-system

# Symmetric Encryption & Decryption System (C++)

## 📌 Overview
This project implements two classical encryption techniques: a polyalphabetic cipher and the rail fence cipher. The program reads plaintext from a file, encrypts it using both methods, then decrypts it back to verify correctness. The rail fence depth is provided by the user as input.

## 🚀 Features
- Polyalphabetic cipher encryption and decryption
- Rail fence cipher encryption and decryption
- File-based input and output handling
- User-defined rail depth parameter
- Verification through decryption output

## 🛠️ Tech Stack
- C++
- File I/O
- String manipulation
- Algorithm design

## ▶️ How to Run

### 1. Clone the repository
git clone https://github.com/your-username/symmetric-encryption-cpp.git

### 2. Navigate to source folder
cd symmetric-encryption-cpp/src

### 3. Compile
g++ main.cpp -o app

### 4. Run
./app

### 5. Input
- Enter rail fence depth when prompted
- Ensure input file exists in `/input`

## 📂 Input / Output
- Input file: `/input/sample.txt`
- Output file: `/output/result.txt`

## 🧠 What I Learned
- Implementing classical encryption algorithms
- Working with file streams in C++
- Handling user input dynamically
- Designing multi-step processing systems (encrypt → decrypt → verify)

## 🔐 Algorithms Used

### Polyalphabetic Cipher
- Uses multiple substitution alphabets
- Enhances security over simple substitution ciphers

### Rail Fence Cipher
- Transposition cipher based on zigzag pattern
- Encryption depends on user-defined depth

## 📌 Future Improvements
- Add support for modern encryption algorithms (AES)
- Build a GUI version of the tool
- Improve input validation and error handling

## 📊 Example

Input:
HELLO WORLD

Encrypted (Rail Fence):
HOLEL WRDLO

Decrypted:
HELLO WORLD

## 👤 Author
Mena Mikhail

# Blockchain-LinkedList (C++)

A simple blockchain implementation in C++ with Proof-of-Work, timestamp, tampering, and validation.

## Features
- Block class with index, data, timestamp, nonce, previous hash, and hash
- SHA-256 hashing using OpenSSL
- Mining using Proof-of-Work
- Tampering and validation
- Interactive menu

## How to Compile & Run
1. Compile with OpenSSL library:
   g++ src/main.cpp -o blockchain -lssl -lcrypto
2. Run:
   ./blockchain (Linux/Mac)
   blockchain.exe (Windows)

## Future Improvements
- Dynamic difficulty adjustment
- Save/load blockchain to file
- Digital signatures

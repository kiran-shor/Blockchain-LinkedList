#include <iostream>
#include <vector>
#include <ctime>        // for timestamp
#include <limits>       // for numeric_limits
#include "sha256.h"

using namespace std;

// Block class
class Block {
public:
    int index;
    string data;
    string prevHash;
    string hash;
    int nonce;
    string timestamp;

    // Constructor
    Block(int i, string d, string prev) {
        index = i;
        data = d;
        prevHash = prev;
        nonce = 0;
        timestamp = getTime();   // set timestamp
        mineBlock();
    }

    // Get current time
    string getTime() {
        time_t now = time(0);
        char* dt = ctime(&now);
        return string(dt);
    }

    // Hash calculation
    string calculateHash() {
        string input = to_string(index) + data + prevHash + timestamp + to_string(nonce);
        return sha256(input);
    }

    // Mining
    void mineBlock() {
        string target = "000";

        do {
            nonce++;
            hash = calculateHash();
        } while (hash.substr(0, target.size()) != target);

        cout << "✅ Block mined: " << hash << endl;
    }
};

// Blockchain class
class Blockchain {
private:
    vector<Block> chain;

public:
    Blockchain() {
        chain.push_back(Block(0, "Genesis Block", "0"));
    }

    void addBlock(string data) {
        Block prev = chain.back();
        Block newBlock(chain.size(), data, prev.hash);
        chain.push_back(newBlock);
    }

    void printChain() {
        for (auto &b : chain) {
            cout << "\nIndex: " << b.index << endl;
            cout << "Timestamp: " << b.timestamp;
            cout << "Data: " << b.data << endl;
            cout << "Prev Hash: " << b.prevHash << endl;
            cout << "Hash: " << b.hash << endl;
            cout << "Nonce: " << b.nonce << endl;
            cout << "----------------------\n";
        }
    }

    bool isValid() {
        for (int i = 1; i < chain.size(); i++) {
            if (chain[i].prevHash != chain[i-1].hash)
                return false;

            if (chain[i].hash != chain[i].calculateHash())
                return false;
        }
        return true;
    }

    void tamperBlock(int index, string newData) {
        if (index >= 0 && index < chain.size()) {
            chain[index].data = newData;
            cout << "⚠️ Block tampered!\n";
        } else {
            cout << "❌ Invalid index!\n";
        }
    }

    int getSize() {
        return chain.size();
    }
};

// MAIN MENU
int main() {
    Blockchain bc;
    int choice;
    string data;
    int index;

    while (true) {
        cout << "\n====== BLOCKCHAIN MENU ======\n";
        cout << "1. Add Block\n";
        cout << "2. Print Blockchain\n";
        cout << "3. Tamper Block\n";
        cout << "4. Validate Blockchain\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) { // Check for non-integer input
            cin.clear();          
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "❌ Invalid input! Please enter a number between 1-5.\n";
            continue; 
        }

        switch (choice) {
            case 1:
                cout << "Enter data: ";
                cin.ignore();
                getline(cin, data);
                bc.addBlock(data);
                break;

            case 2:
                bc.printChain();
                break;

            case 3:
                cout << "Enter block index to tamper: ";
                cin >> index;
                cout << "Enter new data: ";
                cin.ignore();
                getline(cin, data);
                bc.tamperBlock(index, data);
                break;

            case 4:
                if (bc.isValid())
                    cout << "✅ Blockchain is valid\n";
                else
                    cout << "❌ Blockchain is NOT valid\n";
                break;

            case 5:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "❌ Invalid choice! Please select a number between 1-5.\n";
        }
    }
}
#include <iostream>
#include <ctime>
#include <limits>
#include "sha256.h"

using namespace std;

// Block (Node of Linked List)
class Block {
public:
    int index;
    string data;
    string prevHash;
    string hash;
    int nonce;
    string timestamp;
    Block* next;   // pointer to next block

    Block(int i, string d, string prev) {
        index = i;
        data = d;
        prevHash = prev;
        nonce = 0;
        timestamp = getTime();
        next = NULL;
        mineBlock();
    }

    string getTime() {
        time_t now = time(0);
        return string(ctime(&now));
    }

    string calculateHash() {
        string input = to_string(index) + data + prevHash + timestamp + to_string(nonce);
        return sha256(input);
    }

    void mineBlock() {
        string target = "000";

        do {
            nonce++;
            hash = calculateHash();
        } while (hash.substr(0, target.size()) != target);

        cout << "✅ Block mined: " << hash << endl;
    }
};

// Blockchain using Linked List
class Blockchain {
private:
    Block* head;
    Block* tail;

public:
    Blockchain() {
        head = new Block(0, "Genesis Block", "0");
        tail = head;
    }

    void addBlock(string data) {
        Block* newBlock = new Block(tail->index + 1, data, tail->hash);
        tail->next = newBlock;
        tail = newBlock;
    }

    void printChain() {
        Block* temp = head;
        while (temp != NULL) {
            cout << "\nIndex: " << temp->index << endl;
            cout << "Timestamp: " << temp->timestamp;
            cout << "Data: " << temp->data << endl;
            cout << "Prev Hash: " << temp->prevHash << endl;
            cout << "Hash: " << temp->hash << endl;
            cout << "Nonce: " << temp->nonce << endl;
            cout << "----------------------\n";
            temp = temp->next;
        }
    }

    bool isValid() {
        Block* temp = head;

        while (temp->next != NULL) {
            if (temp->next->prevHash != temp->hash)
                return false;

            if (temp->next->hash != temp->next->calculateHash())
                return false;

            temp = temp->next;
        }
        return true;
    }

    void tamperBlock(int index, string newData) {
        Block* temp = head;

        while (temp != NULL) {
            if (temp->index == index) {
                temp->data = newData;
                cout << "⚠️ Block tampered!\n";
                return;
            }
            temp = temp->next;
        }

        cout << "❌ Invalid index!\n";
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

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
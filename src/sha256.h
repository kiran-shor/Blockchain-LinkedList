#ifndef SHA256_H
#define SHA256_H

#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

using namespace std;

string sha256(string input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input.c_str(), input.size(), hash);

    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

#endif
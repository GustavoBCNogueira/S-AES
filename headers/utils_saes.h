#ifndef UTILS_SAES_H
#define UTILS_SAES_H
#include <bitset>
#include <vector>
#include <string>
using namespace std;

vector<bitset<16>> string_to_blocks(const string& input);
string bitset16_to_hex(const bitset<16>& b);
string base64_encode(const bitset<16>& b);
vector<bitset<16>> encrypt_saes_ecb(const vector<bitset<16>>& blocks, const bitset<16>& key);

#endif
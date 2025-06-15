#ifndef ENCRYPT_SAES_H
#define ENCRYPT_SAES_H

#include <bits/stdc++.h>

using namespace std;

vector<bitset<4>> substitute_nibbles(bitset<16> &block);
vector<bitset<4>> shift_rows(vector<bitset<4>> &state_array);
vector<bitset<4>> mix_columns(vector<bitset<4>> &state_array);
bitset<16> add_round_key(bitset<16> &block, bitset<16> &words);
vector<bitset<8>> key_expansion(bitset<16> &key, int round);
bitset<16> encrypt_s_aes_block(bitset<16> &block, bitset<16> &key, int round);
vector<bitset<16>> encryption_s_aes_ecb(vector<bitset<16>> &blocks, bitset<16> &key);
vector<bitset<16>> decryption_s_aes_ecb(vector<bitset<16>> &blocks, bitset<16> &key);
vector<bitset<16>> encryption_s_aes_cbc(vector<bitset<16>> &blocks, bitset<16> &key, bitset<16> &iv);
vector<bitset<16>> decryption_s_aes_cbc(vector<bitset<16>> &blocks, bitset<16> &key, bitset<16> &iv);
vector<bitset<16>> encryption_s_aes_cfb(vector<bitset<16>> &blocks, bitset<16> &key, bitset<16> &iv);
vector<bitset<16>> decryption_s_aes_cfb(vector<bitset<16>> &blocks, bitset<16> &key, bitset<16> &iv);
vector<bitset<16>> encryption_s_aes_ofb(vector<bitset<16>> &blocks, bitset<16> &key, bitset<16> &iv);
vector<bitset<16>> decryption_s_aes_ofb(vector<bitset<16>> &blocks, bitset<16> &key, bitset<16> &iv);   

#endif
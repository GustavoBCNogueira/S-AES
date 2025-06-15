#include "../headers/encrypt_saes.h"

using namespace std;

bitset<16> encrypt_s_aes_block(bitset<16> &block, bitset<16> &key, int round) {
    cout << "Initial Block: " << block << endl;
    cout << "Initial Key: " << key << endl;

    // Initial AddRoundKey
    block = add_round_key(block, key);
    cout << "Block after initial AddRoundKey: " << block << endl;

    // Key expansion for the current round
    vector<bitset<8>> round_keys = key_expansion(key, round);
    cout << "Round keys for round " << round << ":" << round_keys[2] << " " << round_keys[3] << endl;

    // Substitute Nibbles
    vector<bitset<4>> state_array = substitute_nibbles(block);
    cout << "State array after Substitute Nibbles: ";
    for (const auto &nibble : state_array) cout << nibble << " ";
    cout << endl;

    // Shift Rows
    state_array = shift_rows(state_array);
    cout << "State array after Shift Rows: ";
    for (const auto &nibble : state_array) cout << nibble << " ";
    cout << endl;

    // Mix Columns (only in first round)
    state_array = mix_columns(state_array);
    cout << "State array after Mix Columns: ";
    for (const auto &nibble : state_array) cout << nibble << " ";
    cout << endl;
    
    // Add Round Key (first round)
    bitset<16> round_key = bitset<16>(round_keys[2].to_ulong() << 8 | round_keys[3].to_ulong());
    block = add_round_key(block, round_key);
    cout << "Block after second Add Round Key: " << block << endl;

    round++;
    cout << "Proceeding to round " << round << endl;

    // Key expansion for the next round
    round_keys = key_expansion(key, round);
    cout << "Round keys for round " << round << ":" << round_keys[0] << " " << round_keys[1] << endl;

    // Substitute Nibbles
    state_array = substitute_nibbles(block);
    cout << "State array after Substitute Nibbles: ";
    for (const auto &nibble : state_array) cout << nibble << " ";
    cout << endl;

    // Shift Rows
    state_array = shift_rows(state_array);
    cout << "State array after Shift Rows: ";
    for (const auto &nibble : state_array) cout << nibble << " ";
    cout << endl;

    // No Mix Columns in last round

    // Add Round Key (last round, use W4 and W5)
    round_key = bitset<16>(round_keys[4].to_ulong() << 8 | round_keys[5].to_ulong());
    block = add_round_key(block, round_key);
    cout << "Block after final Add Round Key: " << block << endl;
    
    return block;
}
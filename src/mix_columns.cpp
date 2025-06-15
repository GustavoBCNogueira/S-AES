// mix_columns.cpp - Implementação da operação MixColumns do S-AES
// Realiza a multiplicação de cada coluna do estado por uma matriz fixa em GF(2^4)
// A matriz utilizada é [1 4; 4 1], onde 1 = 0001 e 4 = 0100 (x^2)
// Todas as operações são feitas no corpo finito GF(2^4) com polinômio x^4 + x + 1

#include <bits/stdc++.h>

using namespace std;

// Função auxiliar para multiplicação em GF(2^4)
// Parâmetros:
//   a, b - nibbles (4 bits) a serem multiplicados
// Retorno:
//   resultado da multiplicação em GF(2^4)
bitset<4> gf4_mul(bitset<4> a, bitset<4> b) {
    uint8_t p = 0, aa = a.to_ulong(), bb = b.to_ulong();
    for (int i = 0; i < 4; ++i) {
        if (bb & 1) p ^= aa;
        bool carry = aa & 0x8;
        aa <<= 1;
        if (carry) aa ^= 0x13; // x^4 + x + 1
        bb >>= 1;
    }
    return bitset<4>(p & 0xF);
}

// Realiza a operação MixColumns no estado do S-AES
// Parâmetros:
//   state_array - vetor de 4 nibbles representando o estado 2x2
// Retorno:
//   novo vetor de 4 nibbles após a multiplicação pela matriz
vector<bitset<4>> mix_columns(vector<bitset<4>> &state_array) {
    // S-AES state is 2x2: [s0 s1; s2 s3]
    // MixColumns matrix: [1 4; 4 1]
    vector<bitset<4>> mixed_state(4);
    mixed_state[0] = gf4_mul(state_array[0], bitset<4>(1)) ^ gf4_mul(state_array[2], bitset<4>(4));
    mixed_state[1] = gf4_mul(state_array[1], bitset<4>(1)) ^ gf4_mul(state_array[3], bitset<4>(4));
    mixed_state[2] = gf4_mul(state_array[0], bitset<4>(4)) ^ gf4_mul(state_array[2], bitset<4>(1));
    mixed_state[3] = gf4_mul(state_array[1], bitset<4>(4)) ^ gf4_mul(state_array[3], bitset<4>(1));
    return mixed_state;
}
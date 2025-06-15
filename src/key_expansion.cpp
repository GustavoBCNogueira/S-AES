// key_expansion.cpp - Implementação da expansão de chave do S-AES
// Expande uma chave de 16 bits em 6 palavras de 8 bits, usando a função g e S-box.
// Segue o princípio do AES real, mas adaptado para o S-AES didático.

#include <bits/stdc++.h>

using namespace std;

// Função g: realiza rotação de nibbles, substituição pela S-box e adição do round constant
// Parâmetros:
//   key   - palavra de 8 bits
//   round - número da rodada (1 ou 2)
// Retorno:
//   palavra de 8 bits transformada
bitset<8> g_function(bitset<8> &key, int round) {
    // S-box de 4 bits
    unordered_map<bitset<4>, bitset<4>> s_box = {
        {bitset<4>("0000"), bitset<4>("1001")}, // 0 -> 9
        {bitset<4>("0001"), bitset<4>("0100")}, // 1 -> 4
        {bitset<4>("0010"), bitset<4>("1010")}, // 2 -> 10
        {bitset<4>("0011"), bitset<4>("1011")}, // 3 -> 11
        {bitset<4>("0100"), bitset<4>("1101")}, // 4 -> 13
        {bitset<4>("0101"), bitset<4>("0001")}, // 5 -> 1
        {bitset<4>("0110"), bitset<4>("1000")}, // 6 -> 8
        {bitset<4>("0111"), bitset<4>("0101")}, // 7 -> 5
        {bitset<4>("1000"), bitset<4>("0110")}, // 8 -> 6
        {bitset<4>("1001"), bitset<4>("0010")}, // 9 -> 2
        {bitset<4>("1010"), bitset<4>("0000")}, // 10 -> 0
        {bitset<4>("1011"), bitset<4>("0011")}, // 11 -> 3
        {bitset<4>("1100"), bitset<4>("1100")}, // 12 -> 12
        {bitset<4>("1101"), bitset<4>("1110")}, // 13 -> 14
        {bitset<4>("1110"), bitset<4>("1111")}, // 14 -> 15
        {bitset<4>("1111"), bitset<4>("0111")}  // 15 -> 7
    };

    // Rotaciona os nibbles: nibble da direita vira esquerda e vice-versa
    bitset<4> left_nibble = bitset<4>(key.to_ulong() & 0xF); // nibble direito
    bitset<4> right_nibble = bitset<4>(key.to_ulong() >> 4); // nibble esquerdo

    // Substituição S-box
    left_nibble = s_box[left_nibble];
    right_nibble = s_box[right_nibble];

    // Round constant: x^{j+2} para o nibble esquerdo, 0 para o direito
    bitset<4> rcon(0);
    if (round == 1) rcon = bitset<4>("1000"); // x^3
    else if (round == 2) rcon = bitset<4>("0011"); // x^4

    left_nibble ^= rcon;

    // Junta os nibbles novamente em 8 bits
    bitset<8> result = bitset<8>((right_nibble.to_ulong() << 4) | left_nibble.to_ulong());
    return result;
}

// Expande a chave de 16 bits em 6 palavras de 8 bits para as rodadas do S-AES
// Parâmetros:
//   key   - chave de 16 bits
//   round - número da rodada (não usado diretamente aqui)
// Retorno:
//   vetor de 6 palavras de 8 bits (w0 a w5)
vector<bitset<8>> key_expansion(bitset<16> &key, int round) {
    vector<bitset<8>> w(6);
    // W0: byte mais significativo, W1: byte menos significativo
    w[0] = bitset<8>((key >> 8).to_ulong() & 0xFF);
    w[1] = bitset<8>(key.to_ulong() & 0xFF);
    // W2 = W0 ^ g(W1, 1)
    w[2] = w[0] ^ g_function(w[1], 1);
    // W3 = W2 ^ W1
    w[3] = w[2] ^ w[1];
    // W4 = W2 ^ g(W3, 2)
    w[4] = w[2] ^ g_function(w[3], 2);
    // W5 = W4 ^ W3
    w[5] = w[4] ^ w[3];
    return w;
}
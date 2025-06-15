// add_round_key.cpp - Função para realizar a operação AddRoundKey do S-AES
// Esta função faz a soma (XOR) bit a bit entre o bloco de dados e a subchave da rodada.
// É uma das operações fundamentais do S-AES e do AES real.

#include <bits/stdc++.h>

using namespace std;

// Realiza a operação AddRoundKey: XOR entre o bloco e a subchave (words)
// Parâmetros:
//   block - bloco de 16 bits a ser cifrado
//   words - subchave de 16 bits da rodada
// Retorno:
//   bloco de 16 bits resultante do XOR
bitset<16> add_round_key(bitset<16> &block, bitset<16> &words) {
    return block ^ words; // Operação XOR bit a bit
}
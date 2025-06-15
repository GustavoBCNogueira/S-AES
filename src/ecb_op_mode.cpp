// ecb_op_mode.cpp - Implementação do modo de operação ECB para o S-AES
// Neste modo, cada bloco de 16 bits é cifrado independentemente com a mesma chave.
// Blocos idênticos geram saídas idênticas, ilustrando a fraqueza do modo ECB.

#include "../headers/ecb_op_mode.h"
#include "../headers/encrypt_saes.h" 
#include <vector>
#include <cstdint>

using namespace std;

// Função para cifrar vários blocos de 16 bits usando o S-AES no modo ECB
// Parâmetros:
//   blocks - vetor de blocos de 16 bits a serem cifrados
//   key    - chave de 16 bits
// Retorno:
//   vetor de blocos cifrados
vector<bitset<16>> encrypt_saes_ecb(const vector<bitset<16>>& blocks, const bitset<16>& key) {
    vector<bitset<16>> encrypted;
    for (const auto& block : blocks) {
        bitset<16> b = block;
        bitset<16> k = key;
        int round = 1;
        bitset<16> results = encrypt_s_aes_block(b, k, round); // Cifra o bloco
        encrypted.push_back(results);
    }
    reverse(encrypted.begin(), encrypted.end()); // Inverte a ordem dos blocos cifrados (opcional)
    return encrypted;
}
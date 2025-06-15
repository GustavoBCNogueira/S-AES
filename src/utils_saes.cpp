// utils_saes.cpp - Funções utilitárias para manipulação de blocos, conversão e codificação base64 para o S-AES
// Cada função está comentada para facilitar o entendimento didático do projeto.

#include "../headers/utils_saes.h"   // Declarações das funções utilitárias
#include "../headers/encrypt_saes.h" // Funções principais do S-AES
#include <sstream>
#include <iomanip>  

using namespace std;

// Converte uma string de texto em um vetor de blocos de 16 bits (bitset<16>),
// agrupando a cada 2 caracteres (cada caractere = 8 bits)
vector<bitset<16>> string_to_blocks(const string& input) {
    vector<bitset<16>> blocks;
    for (size_t i = 0; i < input.size(); i += 2) {
        uint16_t block = 0;
        // O primeiro caractere vai para os 8 bits mais significativos
        block |= (uint8_t)input[i] << 8;
        // O segundo caractere (se existir) vai para os 8 bits menos significativos
        if (i + 1 < input.size())
            block |= (uint8_t)input[i + 1];
        blocks.push_back(bitset<16>(block));
    }
    return blocks;
}

// Converte um bloco de 16 bits (bitset<16>) para uma string hexadecimal (4 dígitos)
string bitset16_to_hex(const bitset<16>& b) {
    stringstream ss;
    ss << hex << setw(4) << setfill('0') << b.to_ulong();
    return ss.str();
}

// Codifica um bloco de 16 bits (bitset<16>) em base64 (apenas para visualização)
string base64_encode(const bitset<16>& b) {
    static const string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    uint32_t val = b.to_ulong();
    string out;
    // Divide os 16 bits em 3 grupos de 6 bits para base64
    out += base64_chars[(val >> 12) & 0x3F];
    out += base64_chars[(val >> 6) & 0x3F];
    out += base64_chars[val & 0x3F];
    out += "="; // padding
    return out;
}
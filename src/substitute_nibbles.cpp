// substitute_nibbles.cpp - Implementação da substituição de nibbles (SubNibbles) do S-AES
// Esta função aplica a S-box de 4 bits a cada nibble do bloco de 16 bits.
// A S-box é fixa e definida conforme a especificação do S-AES.

#include <bits/stdc++.h>

using namespace std;

// Custom comparator para bitset<4> para uso em map
struct Bitset4Less {
    bool operator()(const bitset<4>& a, const bitset<4>& b) const {
        return a.to_ulong() < b.to_ulong();
    }
};

// Função para substituir cada nibble do bloco usando a S-box
// Parâmetros:
//   block - bloco de 16 bits (bitset<16>)
// Retorno:
//   vetor de 4 nibbles (bitset<4>) após substituição pela S-box
vector<bitset<4>> substitute_nibbles(bitset<16> &block) {
    map<bitset<4>, bitset<4>, Bitset4Less> s_box = {
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
    vector<bitset<4>> state_array(4);

    // Para cada nibble do bloco, aplica a S-box
    for (int i = 0; i < 4; i++) {
        bitset<4> nibble((block >> (i * 4)).to_ulong() & 0xF);
        state_array[i] = s_box[nibble];
    }
    
    reverse(state_array.begin(), state_array.end()); // Inverte a ordem dos nibbles (conforme convenção)

    return state_array;
}

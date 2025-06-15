// shift_rows.cpp - Implementação da operação ShiftRows do S-AES
// Nesta operação, a primeira linha do estado permanece igual e a segunda linha é invertida (swap).
// Isso corresponde a um deslocamento circular à esquerda na segunda linha da matriz 2x2 de nibbles.

#include <bits/stdc++.h>

using namespace std;

// Função para realizar o ShiftRows no estado do S-AES
// Parâmetros:
//   state_array - vetor de 4 nibbles representando o estado 2x2
// Retorno:
//   novo vetor de 4 nibbles após o shift
vector<bitset<4>> shift_rows(vector<bitset<4>> &state_array) {
    // O estado é [s0 s1; s2 s3]. Após o shift: [s0 s1; s3 s2]
    vector<bitset<4>> shifted_state = {state_array[0], state_array[1], state_array[3], state_array[2]};
    return shifted_state;
}
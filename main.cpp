// Este arquivo demonstra a cifragem S-AES didática e a cifragem AES (OpenSSL) em vários modos de operação.
// O código está comentado detalhadamente para fins didáticos.

#include "headers/encrypt_saes.h" // Funções do S-AES
#include "headers/utils_saes.h"    // Funções utilitárias para blocos, base64, etc.
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <openssl/evp.h> // Biblioteca OpenSSL para AES 
#include <openssl/rand.h>
#include <chrono> // Biblioteca para medir tempo de execução
using namespace std;

// Função para codificar um vetor de bytes em base64 (para saída amigável)
string base64_encode_openssl(const vector<unsigned char>& data) {
    static const char* base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string out;
    int val = 0, valb = -6;
    for (unsigned char c : data) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

// Função para cifrar um texto com AES real em um modo específico usando OpenSSL
// Recebe o modo (ECB, CBC, etc), o texto plano, a chave e o IV
void aes_encrypt(const string& mode, const vector<unsigned char>& plaintext, const vector<unsigned char>& key, const vector<unsigned char>& iv) {
    // Inclui o namespace chrono para facilitar o uso das funções de tempo
    using namespace chrono;
    // Seleciona o modo de operação do AES
    const EVP_CIPHER* cipher = nullptr;
    if (mode == "ECB") cipher = EVP_aes_128_ecb();
    else if (mode == "CBC") cipher = EVP_aes_128_cbc();
    else if (mode == "CFB") cipher = EVP_aes_128_cfb128();
    else if (mode == "OFB") cipher = EVP_aes_128_ofb();
    else if (mode == "CTR") cipher = EVP_aes_128_ctr();
    else { cout << "Modo não suportado!" << endl; return; }

    // Cria o contexto de cifragem
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    // Vetor para armazenar o texto cifrado (pode ser maior que o texto original)
    vector<unsigned char> ciphertext(plaintext.size() + EVP_CIPHER_block_size(cipher));
    int len, ciphertext_len = 0;

    // Marca o tempo de início da cifragem
    auto start = high_resolution_clock::now();

    // Inicializa a cifragem com a chave e IV (ou NULL para ECB)
    EVP_EncryptInit_ex(ctx, cipher, nullptr, key.data(), (mode == "ECB" ? nullptr : iv.data()));
    // Cifra o texto plano
    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(), plaintext.size());
    ciphertext_len = len;
    // Finaliza a cifragem (preenche o bloco final, se necessário)
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;
    // Libera o contexto
    EVP_CIPHER_CTX_free(ctx);

    // Marca o tempo de fim da cifragem
    auto end = high_resolution_clock::now();
    // Calcula a duração em microssegundos
    auto duration = duration_cast<microseconds>(end - start);

    ciphertext.resize(ciphertext_len); // Ajusta o tamanho do vetor para o texto cifrado real
    // Exibe o resultado em base64
    cout << "Modo " << mode << ":\nBase64: " << base64_encode_openssl(ciphertext) << endl;
    // Exibe o tempo de execução em milissegundos
    cout << "Tempo de execução: " << duration.count() / 1000.0 << " ms" << endl;
}

int main() {
    // --- S-AES ---
    // Entrada e cifragem didática usando o S-AES
    string mensagem;
    cout << "Digite a mensagem (até 2 caracteres por bloco): ";
    getline(cin, mensagem);

    // Chave fixa de 16 bits para o S-AES
    bitset<16> key("1010011100111011");
    // Converte a string em blocos de 16 bits
    vector<bitset<16>> blocks = string_to_blocks(mensagem);

    cout << "Chave: " << key << endl;

    // Cifra todos os blocos usando o modo ECB do S-AES
    vector<bitset<16>> encrypted_blocks = encrypt_saes_ecb(blocks, key);

    // Exibe cada bloco cifrado em binário, hexadecimal e base64
    for (size_t i = 0; i < encrypted_blocks.size(); ++i) {
        cout << "\nBloco " << i << ": " << blocks[i] << endl;
        cout << "Bloco cifrado (binário): " << encrypted_blocks[i] << endl;
        cout << "Bloco cifrado (hex): " << bitset16_to_hex(encrypted_blocks[i]) << endl;
        cout << "Bloco cifrado (base64): " << base64_encode(encrypted_blocks[i]) << endl;
    }

    // --- AES OpenSSL ---
    // Entrada e cifragem real usando a biblioteca OpenSSL
    cout << "\n--- AES OpenSSL ---" << endl;
    cout << "Digite a mensagem: ";
    getline(cin, mensagem);
    vector<unsigned char> plaintext(mensagem.begin(), mensagem.end());

    // Gera chave e IV aleatórios de 128 bits (16 bytes)
    vector<unsigned char> key_aes(16, 0x00);
    RAND_bytes(key_aes.data(), key_aes.size());
    vector<unsigned char> iv(16, 0x00);
    RAND_bytes(iv.data(), iv.size());

    // Exibe chave e IV em hexadecimal
    cout << "Chave (hex): ";
    for (auto c : key_aes) cout << hex << setw(2) << setfill('0') << (int)c;
    cout << "\nIV (hex): ";
    for (auto c : iv) cout << hex << setw(2) << setfill('0') << (int)c;
    cout << endl;

    // Cifra a mensagem em todos os modos de operação AES
    aes_encrypt("ECB", plaintext, key_aes, iv);
    aes_encrypt("CBC", plaintext, key_aes, iv);
    aes_encrypt("CFB", plaintext, key_aes, iv);
    aes_encrypt("OFB", plaintext, key_aes, iv);
    aes_encrypt("CTR", plaintext, key_aes, iv);
    return 0;
}
